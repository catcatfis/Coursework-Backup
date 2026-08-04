package sjk.sjksj.service;

import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.stereotype.Service;

import java.util.List;
import java.util.Map;

@Service
public class DataQueryService {

    private final JdbcTemplate jdbc;

    public DataQueryService(JdbcTemplate jdbcTemplate) {
        this.jdbc = jdbcTemplate;
    }

    // q1: 查询某单位在指定日期范围内的预算项目
    public List<Map<String, Object>> queryBudgetByDeptAndDate(String dname, String startDate, String endDate) {
        String sql = "SELECT t.tid, t.dpid, d.dname, t.owid, t.budgetamount, t.budgeter, t.budgetdate, " +
                "t.startdate, t.enddate, t.cname, t.ConstructionContent " +
                "FROM department d JOIN task t ON d.dpid = t.dpid " +
                "WHERE d.dname = ? AND t.budgetdate BETWEEN ? AND ?";
        return jdbc.queryForList(sql, dname, startDate, endDate);
    }

    // q2: 查询某单位在指定日期范围内的结算项目及材料消耗明细
    public List<Map<String, Object>> querySettlementDetail(String dname, String startDate, String endDate) {
        String sql = "SELECT t.tid, d.dname, t.owid, t.ConstructionContent, t.Settlementamount, t.Settlementdate, " +
                "m.itemid, i.itemname, i.unit, m.quantity, m.price " +
                "FROM department d " +
                "JOIN task t ON d.dpid = t.dpid " +
                "JOIN materialconsumption m ON t.tid = m.tid " +
                "JOIN item i ON m.itemid = i.itemid " +
                "WHERE d.dname = ? AND t.Settlementdate BETWEEN ? AND ?";
        return jdbc.queryForList(sql, dname, startDate, endDate);
    }

    // q3: 查询某单位指定日期范围的总预算/总结算/总入账金额
    public Map<String, Object> queryAmountSummary(String dname, String startDate, String endDate) {
        String sql = "SELECT " +
                "(SELECT COALESCE(SUM(t.budgetamount),0) FROM department d JOIN task t ON d.dpid=t.dpid " +
                "WHERE d.dname=? AND t.budgetdate BETWEEN ? AND ?) AS totalBudget, " +
                "(SELECT COALESCE(SUM(t.Settlementamount),0) FROM department d JOIN task t ON d.dpid=t.dpid " +
                "WHERE d.dname=? AND t.Settlementdate BETWEEN ? AND ?) AS totalSettlement, " +
                "(SELECT COALESCE(SUM(t.Amountcredited),0) FROM department d JOIN task t ON d.dpid=t.dpid " +
                "WHERE d.dname=? AND t.Amountcreditedate BETWEEN ? AND ?) AS totalCredited";
        return jdbc.queryForMap(sql, dname, startDate, endDate, dname, startDate, endDate, dname, startDate, endDate);
    }

    // q4: 查询已结算但未入账的项目
    public List<Map<String, Object>> querySettledNotCredited(String startDate, String endDate) {
        String sql = "SELECT t.tid, t.dpid, t.owid, t.Settlementamount, t.Settlementdate, " +
                "t.Amountcredited, t.Amountcreditedate, t.cname, t.ConstructionContent " +
                "FROM task t " +
                "WHERE t.Settlementdate BETWEEN ? AND ? AND t.Amountcredited IS NULL";
        return jdbc.queryForList(sql, startDate, endDate);
    }

    // q5: 查询各施工单位的项目统计（项目数量、结算金额总和、平均、最高、最低）
    public List<Map<String, Object>> queryConstructionUnitStats() {
        String sql = "SELECT t.cname AS constructionUnit, " +
                "COUNT(*) AS projectCount, " +
                "SUM(t.Settlementamount) AS totalSettlement, " +
                "AVG(t.Settlementamount) AS avgSettlement, " +
                "MAX(t.Settlementamount) AS maxSettlement, " +
                "MIN(t.Settlementamount) AS minSettlement " +
                "FROM task t WHERE t.cname IS NOT NULL " +
                "GROUP BY t.cname ORDER BY SUM(t.Settlementamount) DESC";
        return jdbc.queryForList(sql);
    }

    // q6: 查询消耗某材料超过指定金额的项目
    public List<Map<String, Object>> queryMaterialOverAmount(String itemname, double amount) {
        String sql = "SELECT t.tid, d.dname AS departmentName, i.itemname AS materialName, " +
                "m.quantity, m.price " +
                "FROM task t " +
                "JOIN department d ON t.dpid = d.dpid " +
                "JOIN materialconsumption m ON t.tid = m.tid " +
                "JOIN item i ON m.itemid = i.itemid " +
                "WHERE i.itemname = ? AND m.price > ? " +
                "AND t.tid IN (" +
                "  SELECT mc.tid FROM materialconsumption mc " +
                "  JOIN item it ON mc.itemid = it.itemid " +
                "  WHERE it.itemname = ? AND mc.price > ?" +
                ")";
        return jdbc.queryForList(sql, itemname, amount, itemname, amount);
    }

    // 获取所有部门名称（供下拉选择）
    public List<String> getAllDepartmentNames() {
        return jdbc.queryForList("SELECT dname FROM department ORDER BY dpid", String.class);
    }

    // 获取所有材料名称
    public List<String> getAllItemNames() {
        return jdbc.queryForList("SELECT itemname FROM item ORDER BY itemid", String.class);
    }

    // 查询采油一矿所有作业项目（通过视图）
    public List<Map<String, Object>> queryCaiYouYiKuangTasks() {
        String sql = "SELECT t.* FROM task t " +
                "JOIN department d ON t.dpid = d.dpid " +
                "WHERE d.dpid LIKE '112201%'";
        return jdbc.queryForList(sql);
    }

    // 查询入账人员列表
    public List<Map<String, Object>> queryAllCreditedPersons() {
        return jdbc.queryForList("SELECT DISTINCT Amountcrediter AS creditedPerson FROM task WHERE Amountcrediter IS NOT NULL");
    }

    // 查询某单位按入账金额排序的作业项目
    public List<Map<String, Object>> queryTasksByDeptOrderByCredited(String dname) {
        String sql = "SELECT t.tid, t.dpid, d.dname, t.owid, t.budgetamount, t.Settlementamount, " +
                "t.Amountcredited, t.cname, t.ConstructionContent " +
                "FROM department d JOIN task t ON d.dpid = t.dpid " +
                "WHERE d.dname = ? ORDER BY t.Amountcredited DESC";
        return jdbc.queryForList(sql, dname);
    }
}
