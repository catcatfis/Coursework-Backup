package sjk.sjksj.controller;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import sjk.sjksj.service.DataQueryService;

import java.util.List;
import java.util.Map;

@Controller
@RequestMapping("/query")
public class QueryController {

    private final DataQueryService queryService;

    public QueryController(DataQueryService queryService) {
        this.queryService = queryService;
    }

    // 查询首页
    @GetMapping
    public String queryIndex(Model model) {
        model.addAttribute("deptNames", queryService.getAllDepartmentNames());
        model.addAttribute("itemNames", queryService.getAllItemNames());
        return "query";
    }

    // Q1: 按单位和日期范围查询预算项目
    @GetMapping("/budget")
    public String queryBudget(@RequestParam String dname,
                              @RequestParam String startDate,
                              @RequestParam String endDate,
                              Model model) {
        List<Map<String, Object>> results = queryService.queryBudgetByDeptAndDate(dname, startDate, endDate);
        model.addAttribute("results", results);
        model.addAttribute("queryTitle", "预算项目查询结果（单位：" + dname + "）");
        model.addAttribute("deptNames", queryService.getAllDepartmentNames());
        model.addAttribute("itemNames", queryService.getAllItemNames());
        return "query";
    }

    // Q2: 按单位和日期范围查询结算项目及材料消耗明细
    @GetMapping("/settlement-detail")
    public String querySettlementDetail(@RequestParam String dname,
                                        @RequestParam String startDate,
                                        @RequestParam String endDate,
                                        Model model) {
        List<Map<String, Object>> results = queryService.querySettlementDetail(dname, startDate, endDate);
        model.addAttribute("results", results);
        model.addAttribute("queryTitle", "结算项目材料消耗明细（单位：" + dname + "）");
        model.addAttribute("deptNames", queryService.getAllDepartmentNames());
        model.addAttribute("itemNames", queryService.getAllItemNames());
        return "query";
    }

    // Q3: 金额汇总查询
    @GetMapping("/amount-summary")
    public String queryAmountSummary(@RequestParam String dname,
                                     @RequestParam String startDate,
                                     @RequestParam String endDate,
                                     Model model) {
        Map<String, Object> summary = queryService.queryAmountSummary(dname, startDate, endDate);
        model.addAttribute("summary", summary);
        model.addAttribute("queryTitle", "金额汇总（单位：" + dname + "）");
        model.addAttribute("deptNames", queryService.getAllDepartmentNames());
        model.addAttribute("itemNames", queryService.getAllItemNames());
        return "query";
    }

    // Q4: 查询已结算但未入账项目
    @GetMapping("/settled-not-credited")
    public String querySettledNotCredited(@RequestParam String startDate,
                                          @RequestParam String endDate,
                                          Model model) {
        List<Map<String, Object>> results = queryService.querySettledNotCredited(startDate, endDate);
        model.addAttribute("results", results);
        model.addAttribute("queryTitle", "已结算未入账项目");
        model.addAttribute("deptNames", queryService.getAllDepartmentNames());
        model.addAttribute("itemNames", queryService.getAllItemNames());
        return "query";
    }

    // Q5: 各施工单位项目统计
    @GetMapping("/construction-stats")
    public String queryConstructionStats(Model model) {
        List<Map<String, Object>> results = queryService.queryConstructionUnitStats();
        model.addAttribute("results", results);
        model.addAttribute("queryTitle", "各施工单位项目统计");
        model.addAttribute("deptNames", queryService.getAllDepartmentNames());
        model.addAttribute("itemNames", queryService.getAllItemNames());
        return "query";
    }

    // Q6: 查询消耗材料超过指定金额的项目
    @GetMapping("/material-over")
    public String queryMaterialOver(@RequestParam String itemname,
                                    @RequestParam double amount,
                                    Model model) {
        List<Map<String, Object>> results = queryService.queryMaterialOverAmount(itemname, amount);
        model.addAttribute("results", results);
        model.addAttribute("queryTitle", "材料「" + itemname + "」消耗超过" + amount + "元的项目");
        model.addAttribute("deptNames", queryService.getAllDepartmentNames());
        model.addAttribute("itemNames", queryService.getAllItemNames());
        return "query";
    }

    // 查询入账人员
    @GetMapping("/credited-persons")
    public String queryCreditedPersons(Model model) {
        List<Map<String, Object>> results = queryService.queryAllCreditedPersons();
        model.addAttribute("results", results);
        model.addAttribute("queryTitle", "入账人员列表");
        model.addAttribute("deptNames", queryService.getAllDepartmentNames());
        model.addAttribute("itemNames", queryService.getAllItemNames());
        return "query";
    }

    // 按单位查询并按入账金额排序
    @GetMapping("/dept-credited")
    public String queryDeptCredited(@RequestParam String dname, Model model) {
        List<Map<String, Object>> results = queryService.queryTasksByDeptOrderByCredited(dname);
        model.addAttribute("results", results);
        model.addAttribute("queryTitle", dname + " 作业项目（按入账金额排序）");
        model.addAttribute("deptNames", queryService.getAllDepartmentNames());
        model.addAttribute("itemNames", queryService.getAllItemNames());
        return "query";
    }

    // 查询采油一矿所有作业项目
    @GetMapping("/caiyou-yikuang")
    public String queryCaiYouYiKuang(Model model) {
        List<Map<String, Object>> results = queryService.queryCaiYouYiKuangTasks();
        model.addAttribute("results", results);
        model.addAttribute("queryTitle", "采油一矿所有作业项目");
        model.addAttribute("deptNames", queryService.getAllDepartmentNames());
        model.addAttribute("itemNames", queryService.getAllItemNames());
        return "query";
    }
}
