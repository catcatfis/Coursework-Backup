package sjk.sjksj.service;

import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.jdbc.core.RowMapper;
import org.springframework.stereotype.Service;
import sjk.sjksj.entity.*;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.List;

@Service
public class DataService {

    private final JdbcTemplate jdbc;

    public DataService(JdbcTemplate jdbcTemplate) {
        this.jdbc = jdbcTemplate;
    }

    // ========== Department ==========
    public List<Department> findAllDepartments() {
        return jdbc.query("SELECT * FROM department", departmentRowMapper());
    }

    public Department findDepartmentById(String dpid) {
        List<Department> list = jdbc.query("SELECT * FROM department WHERE dpid=?", departmentRowMapper(), dpid);
        return list.isEmpty() ? null : list.get(0);
    }

    public void insertDepartment(Department dept) {
        jdbc.update("INSERT INTO department(dpid, dname) VALUES(?,?)", dept.getDpid(), dept.getDname());
    }

    public void updateDepartment(Department dept) {
        jdbc.update("UPDATE department SET dname=? WHERE dpid=?", dept.getDname(), dept.getDpid());
    }

    public void deleteDepartment(String dpid) {
        jdbc.update("DELETE FROM department WHERE dpid=?", dpid);
    }

    private RowMapper<Department> departmentRowMapper() {
        return (ResultSet rs, int rowNum) -> {
            Department d = new Department();
            d.setDpid(rs.getString("dpid"));
            d.setDname(rs.getString("dname"));
            return d;
        };
    }

    // ========== OilWater ==========
    public List<OilWater> findAllOilWaters() {
        return jdbc.query("SELECT * FROM oil_water", oilWaterRowMapper());
    }

    public OilWater findOilWaterById(String owid) {
        List<OilWater> list = jdbc.query("SELECT * FROM oil_water WHERE owid=?", oilWaterRowMapper(), owid);
        return list.isEmpty() ? null : list.get(0);
    }

    public void insertOilWater(OilWater ow) {
        jdbc.update("INSERT INTO oil_water(owid, owname, dpid) VALUES(?,?,?)", ow.getOwid(), ow.getOwname(), ow.getDpid());
    }

    public void updateOilWater(OilWater ow) {
        jdbc.update("UPDATE oil_water SET owname=?, dpid=? WHERE owid=?", ow.getOwname(), ow.getDpid(), ow.getOwid());
    }

    public void deleteOilWater(String owid) {
        jdbc.update("DELETE FROM oil_water WHERE owid=?", owid);
    }

    private RowMapper<OilWater> oilWaterRowMapper() {
        return (ResultSet rs, int rowNum) -> {
            OilWater ow = new OilWater();
            ow.setOwid(rs.getString("owid"));
            ow.setOwname(rs.getString("owname"));
            ow.setDpid(rs.getString("dpid"));
            return ow;
        };
    }

    // ========== Constructio ==========
    public List<Constructio> findAllConstructions() {
        return jdbc.query("SELECT * FROM Constructio", constructioRowMapper());
    }

    public void insertConstructio(Constructio c) {
        jdbc.update("INSERT INTO Constructio(cname) VALUES(?)", c.getCname());
    }

    public void updateConstructio(String oldCname, String newCname) {
        jdbc.update("UPDATE Constructio SET cname=? WHERE cname=?", newCname, oldCname);
    }

    public void deleteConstructio(String cname) {
        jdbc.update("DELETE FROM Constructio WHERE cname=?", cname);
    }

    private RowMapper<Constructio> constructioRowMapper() {
        return (ResultSet rs, int rowNum) -> {
            Constructio c = new Constructio();
            c.setCname(rs.getString("cname"));
            return c;
        };
    }

    // ========== Item ==========
    public List<Item> findAllItems() {
        return jdbc.query("SELECT * FROM item", itemRowMapper());
    }

    public Item findItemById(String itemid) {
        List<Item> list = jdbc.query("SELECT * FROM item WHERE itemid=?", itemRowMapper(), itemid);
        return list.isEmpty() ? null : list.get(0);
    }

    public void insertItem(Item item) {
        jdbc.update("INSERT INTO item(itemid, itemname, unit, uprice) VALUES(?,?,?,?)",
                item.getItemid(), item.getItemname(), item.getUnit(), item.getUprice());
    }

    public void updateItem(Item item) {
        jdbc.update("UPDATE item SET itemname=?, unit=?, uprice=? WHERE itemid=?",
                item.getItemname(), item.getUnit(), item.getUprice(), item.getItemid());
    }

    public void deleteItem(String itemid) {
        jdbc.update("DELETE FROM item WHERE itemid=?", itemid);
    }

    private RowMapper<Item> itemRowMapper() {
        return (ResultSet rs, int rowNum) -> {
            Item item = new Item();
            item.setItemid(rs.getString("itemid"));
            item.setItemname(rs.getString("itemname"));
            item.setUnit(rs.getString("unit"));
            item.setUprice(rs.getInt("uprice"));
            return item;
        };
    }

    // ========== Task ==========
    public List<Task> findAllTasks() {
        return jdbc.query("SELECT * FROM task", taskRowMapper());
    }

    public Task findTaskById(String tid) {
        List<Task> list = jdbc.query("SELECT * FROM task WHERE tid=?", taskRowMapper(), tid);
        return list.isEmpty() ? null : list.get(0);
    }

    public void insertTask(Task t) {
        jdbc.update("INSERT INTO task(tid,dpid,owid,budgetamount,budgeter,budgetdate,startdate,enddate," +
                        "cname,ConstructionContent,materialcost,laborcost,Equipmentcost,othercost," +
                        "Settlementamount,Settlementer,Settlementdate,Amountcredited,Amountcrediter,Amountcreditedate) " +
                        "VALUES(?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)",
                t.getTid(), t.getDpid(), t.getOwid(), t.getBudgetamount(), t.getBudgeter(),
                t.getBudgetdate(), t.getStartdate(), t.getEnddate(), t.getCname(),
                t.getConstructionContent(), t.getMaterialcost(), t.getLaborcost(),
                t.getEquipmentcost(), t.getOthercost(), t.getSettlementamount(),
                t.getSettlementer(), t.getSettlementdate(), t.getAmountcredited(),
                t.getAmountcrediter(), t.getAmountcreditedate());
    }

    public void updateTask(Task t) {
        jdbc.update("UPDATE task SET dpid=?,owid=?,budgetamount=?,budgeter=?,budgetdate=?,startdate=?,enddate=?," +
                        "cname=?,ConstructionContent=?,materialcost=?,laborcost=?,Equipmentcost=?,othercost=?," +
                        "Settlementamount=?,Settlementer=?,Settlementdate=?,Amountcredited=?,Amountcrediter=?,Amountcreditedate=? " +
                        "WHERE tid=?",
                t.getDpid(), t.getOwid(), t.getBudgetamount(), t.getBudgeter(),
                t.getBudgetdate(), t.getStartdate(), t.getEnddate(), t.getCname(),
                t.getConstructionContent(), t.getMaterialcost(), t.getLaborcost(),
                t.getEquipmentcost(), t.getOthercost(), t.getSettlementamount(),
                t.getSettlementer(), t.getSettlementdate(), t.getAmountcredited(),
                t.getAmountcrediter(), t.getAmountcreditedate(), t.getTid());
    }

    public void deleteTask(String tid) {
        jdbc.update("DELETE FROM materialconsumption WHERE tid=?", tid);
        jdbc.update("DELETE FROM task WHERE tid=?", tid);
    }

    private RowMapper<Task> taskRowMapper() {
        return (ResultSet rs, int rowNum) -> {
            Task t = new Task();
            t.setTid(rs.getString("tid"));
            t.setDpid(rs.getString("dpid"));
            t.setOwid(rs.getString("owid"));
            t.setBudgetamount(rs.getDouble("budgetamount"));
            t.setBudgeter(rs.getString("budgeter"));
            t.setBudgetdate(rs.getDate("budgetdate") != null ? rs.getDate("budgetdate").toLocalDate() : null);
            t.setStartdate(rs.getDate("startdate") != null ? rs.getDate("startdate").toLocalDate() : null);
            t.setEnddate(rs.getDate("enddate") != null ? rs.getDate("enddate").toLocalDate() : null);
            t.setCname(rs.getString("cname"));
            t.setConstructionContent(rs.getString("ConstructionContent"));
            t.setMaterialcost(rs.getDouble("materialcost"));
            t.setLaborcost(rs.getDouble("laborcost"));
            t.setEquipmentcost(rs.getDouble("Equipmentcost"));
            t.setOthercost(rs.getDouble("othercost"));
            t.setSettlementamount(rs.getDouble("Settlementamount"));
            t.setSettlementer(rs.getString("Settlementer"));
            t.setSettlementdate(rs.getDate("Settlementdate") != null ? rs.getDate("Settlementdate").toLocalDate() : null);
            t.setAmountcredited(rs.getDouble("Amountcredited"));
            t.setAmountcrediter(rs.getString("Amountcrediter"));
            t.setAmountcreditedate(rs.getDate("Amountcreditedate") != null ? rs.getDate("Amountcreditedate").toLocalDate() : null);
            return t;
        };
    }

    // ========== MaterialConsumption ==========
    public List<MaterialConsumption> findAllMaterialConsumptions() {
        return jdbc.query("SELECT * FROM materialconsumption", mcRowMapper());
    }

    public List<MaterialConsumption> findMaterialConsumptionsByTid(String tid) {
        return jdbc.query("SELECT * FROM materialconsumption WHERE tid=?", mcRowMapper(), tid);
    }

    public void insertMaterialConsumption(MaterialConsumption mc) {
        jdbc.update("INSERT INTO materialconsumption(tid, itemid, quantity, price) VALUES(?,?,?,?)",
                mc.getTid(), mc.getItemid(), mc.getQuantity(), mc.getPrice());
    }

    public void updateMaterialConsumption(MaterialConsumption mc, String oldTid, String oldItemid) {
        jdbc.update("UPDATE materialconsumption SET tid=?, itemid=?, quantity=?, price=? WHERE tid=? AND itemid=?",
                mc.getTid(), mc.getItemid(), mc.getQuantity(), mc.getPrice(), oldTid, oldItemid);
    }

    public void deleteMaterialConsumption(String tid, String itemid) {
        jdbc.update("DELETE FROM materialconsumption WHERE tid=? AND itemid=?", tid, itemid);
    }

    private RowMapper<MaterialConsumption> mcRowMapper() {
        return (ResultSet rs, int rowNum) -> {
            MaterialConsumption mc = new MaterialConsumption();
            mc.setTid(rs.getString("tid"));
            mc.setItemid(rs.getString("itemid"));
            mc.setQuantity(rs.getInt("quantity"));
            mc.setPrice(rs.getDouble("price"));
            return mc;
        };
    }
}
