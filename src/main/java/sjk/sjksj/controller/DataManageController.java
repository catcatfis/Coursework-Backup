package sjk.sjksj.controller;

import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;
import sjk.sjksj.entity.*;
import sjk.sjksj.service.DataService;

@Controller
@RequestMapping("/manage")
public class DataManageController {

    private final DataService dataService;

    public DataManageController(DataService dataService) {
        this.dataService = dataService;
    }

    // ========== 数据管理首页 ==========
    @GetMapping
    public String manage(Model model) {
        model.addAttribute("departments", dataService.findAllDepartments());
        model.addAttribute("oilWaters", dataService.findAllOilWaters());
        model.addAttribute("constructions", dataService.findAllConstructions());
        model.addAttribute("items", dataService.findAllItems());
        model.addAttribute("tasks", dataService.findAllTasks());
        model.addAttribute("materialConsumptions", dataService.findAllMaterialConsumptions());
        return "manage";
    }

    // ========== 单位代码表 ==========
    @GetMapping("/department/add")
    public String addDepartmentForm(Model model) {
        model.addAttribute("department", new Department());
        model.addAttribute("action", "add");
        return "forms/department-form";
    }

    @PostMapping("/department/save")
    public String saveDepartment(@ModelAttribute Department department, RedirectAttributes ra) {
        try {
            if (dataService.findDepartmentById(department.getDpid()) == null) {
                dataService.insertDepartment(department);
                ra.addFlashAttribute("msg", "添加成功！");
            } else {
                dataService.updateDepartment(department);
                ra.addFlashAttribute("msg", "修改成功！");
            }
        } catch (Exception e) {
            ra.addFlashAttribute("error", "操作失败：" + e.getMessage());
        }
        return "redirect:/manage";
    }

    @GetMapping("/department/edit/{dpid}")
    public String editDepartmentForm(@PathVariable String dpid, Model model) {
        Department dept = dataService.findDepartmentById(dpid);
        model.addAttribute("department", dept);
        model.addAttribute("action", "edit");
        return "forms/department-form";
    }

    @GetMapping("/department/delete/{dpid}")
    public String deleteDepartment(@PathVariable String dpid, RedirectAttributes ra) {
        try {
            dataService.deleteDepartment(dpid);
            ra.addFlashAttribute("msg", "删除成功！");
        } catch (Exception e) {
            ra.addFlashAttribute("error", "删除失败：" + e.getMessage());
        }
        return "redirect:/manage";
    }

    // ========== 油水井表 ==========
    @GetMapping("/oilwater/add")
    public String addOilWaterForm(Model model) {
        model.addAttribute("oilWater", new OilWater());
        model.addAttribute("departments", dataService.findAllDepartments());
        model.addAttribute("action", "add");
        return "forms/oilwater-form";
    }

    @PostMapping("/oilwater/save")
    public String saveOilWater(@ModelAttribute OilWater oilWater, RedirectAttributes ra) {
        try {
            if (dataService.findOilWaterById(oilWater.getOwid()) == null) {
                dataService.insertOilWater(oilWater);
                ra.addFlashAttribute("msg", "添加成功！");
            } else {
                dataService.updateOilWater(oilWater);
                ra.addFlashAttribute("msg", "修改成功！");
            }
        } catch (Exception e) {
            ra.addFlashAttribute("error", "操作失败：" + e.getMessage());
        }
        return "redirect:/manage";
    }

    @GetMapping("/oilwater/edit/{owid}")
    public String editOilWaterForm(@PathVariable String owid, Model model) {
        OilWater ow = dataService.findOilWaterById(owid);
        model.addAttribute("oilWater", ow);
        model.addAttribute("departments", dataService.findAllDepartments());
        model.addAttribute("action", "edit");
        return "forms/oilwater-form";
    }

    @GetMapping("/oilwater/delete/{owid}")
    public String deleteOilWater(@PathVariable String owid, RedirectAttributes ra) {
        try {
            dataService.deleteOilWater(owid);
            ra.addFlashAttribute("msg", "删除成功！");
        } catch (Exception e) {
            ra.addFlashAttribute("error", "删除失败：" + e.getMessage());
        }
        return "redirect:/manage";
    }

    // ========== 施工单位表 ==========
    @GetMapping("/constructio/add")
    public String addConstructioForm(Model model) {
        model.addAttribute("constructio", new Constructio());
        model.addAttribute("action", "add");
        return "forms/constructio-form";
    }

    @PostMapping("/constructio/save")
    public String saveConstructio(@ModelAttribute Constructio constructio,
                                  @RequestParam(required = false) String oldCname,
                                  RedirectAttributes ra) {
        try {
            if ("add".equals(constructio.getCname()) || oldCname == null || oldCname.isEmpty()) {
                dataService.insertConstructio(constructio);
                ra.addFlashAttribute("msg", "添加成功！");
            } else {
                dataService.updateConstructio(oldCname, constructio.getCname());
                ra.addFlashAttribute("msg", "修改成功！");
            }
        } catch (Exception e) {
            ra.addFlashAttribute("error", "操作失败：" + e.getMessage());
        }
        return "redirect:/manage";
    }

    @GetMapping("/constructio/delete/{cname}")
    public String deleteConstructio(@PathVariable String cname, RedirectAttributes ra) {
        try {
            dataService.deleteConstructio(cname);
            ra.addFlashAttribute("msg", "删除成功！");
        } catch (Exception e) {
            ra.addFlashAttribute("error", "删除失败：" + e.getMessage());
        }
        return "redirect:/manage";
    }

    // ========== 物码表 ==========
    @GetMapping("/item/add")
    public String addItemForm(Model model) {
        model.addAttribute("item", new Item());
        model.addAttribute("action", "add");
        return "forms/item-form";
    }

    @PostMapping("/item/save")
    public String saveItem(@ModelAttribute Item item, RedirectAttributes ra) {
        try {
            if (dataService.findItemById(item.getItemid()) == null) {
                dataService.insertItem(item);
                ra.addFlashAttribute("msg", "添加成功！");
            } else {
                dataService.updateItem(item);
                ra.addFlashAttribute("msg", "修改成功！");
            }
        } catch (Exception e) {
            ra.addFlashAttribute("error", "操作失败：" + e.getMessage());
        }
        return "redirect:/manage";
    }

    @GetMapping("/item/edit/{itemid}")
    public String editItemForm(@PathVariable String itemid, Model model) {
        Item item = dataService.findItemById(itemid);
        model.addAttribute("item", item);
        model.addAttribute("action", "edit");
        return "forms/item-form";
    }

    @GetMapping("/item/delete/{itemid}")
    public String deleteItem(@PathVariable String itemid, RedirectAttributes ra) {
        try {
            dataService.deleteItem(itemid);
            ra.addFlashAttribute("msg", "删除成功！");
        } catch (Exception e) {
            ra.addFlashAttribute("error", "删除失败：" + e.getMessage());
        }
        return "redirect:/manage";
    }

    // ========== 作业表 ==========
    @GetMapping("/task/add")
    public String addTaskForm(Model model) {
        model.addAttribute("task", new Task());
        model.addAttribute("departments", dataService.findAllDepartments());
        model.addAttribute("oilWaters", dataService.findAllOilWaters());
        model.addAttribute("constructions", dataService.findAllConstructions());
        model.addAttribute("action", "add");
        return "forms/task-form";
    }

    @PostMapping("/task/save")
    public String saveTask(@ModelAttribute Task task, RedirectAttributes ra) {
        try {
            if (dataService.findTaskById(task.getTid()) == null) {
                dataService.insertTask(task);
                ra.addFlashAttribute("msg", "添加成功！");
            } else {
                dataService.updateTask(task);
                ra.addFlashAttribute("msg", "修改成功！");
            }
        } catch (Exception e) {
            ra.addFlashAttribute("error", "操作失败：" + e.getMessage());
        }
        return "redirect:/manage";
    }

    @GetMapping("/task/edit/{tid}")
    public String editTaskForm(@PathVariable String tid, Model model) {
        Task task = dataService.findTaskById(tid);
        model.addAttribute("task", task);
        model.addAttribute("departments", dataService.findAllDepartments());
        model.addAttribute("oilWaters", dataService.findAllOilWaters());
        model.addAttribute("constructions", dataService.findAllConstructions());
        model.addAttribute("action", "edit");
        return "forms/task-form";
    }

    @GetMapping("/task/delete/{tid}")
    public String deleteTask(@PathVariable String tid, RedirectAttributes ra) {
        try {
            dataService.deleteTask(tid);
            ra.addFlashAttribute("msg", "删除成功！");
        } catch (Exception e) {
            ra.addFlashAttribute("error", "删除失败：" + e.getMessage());
        }
        return "redirect:/manage";
    }

    // ========== 材料消耗表 ==========
    @GetMapping("/material/add")
    public String addMaterialForm(Model model) {
        model.addAttribute("mc", new MaterialConsumption());
        model.addAttribute("tasks", dataService.findAllTasks());
        model.addAttribute("items", dataService.findAllItems());
        model.addAttribute("action", "add");
        return "forms/material-form";
    }

    @PostMapping("/material/save")
    public String saveMaterial(@ModelAttribute MaterialConsumption mc,
                               @RequestParam(required = false) String oldTid,
                               @RequestParam(required = false) String oldItemid,
                               RedirectAttributes ra) {
        try {
            if (oldTid == null || oldTid.isEmpty()) {
                dataService.insertMaterialConsumption(mc);
                ra.addFlashAttribute("msg", "添加成功！");
            } else {
                dataService.updateMaterialConsumption(mc, oldTid, oldItemid);
                ra.addFlashAttribute("msg", "修改成功！");
            }
        } catch (Exception e) {
            ra.addFlashAttribute("error", "操作失败：" + e.getMessage());
        }
        return "redirect:/manage";
    }

    @GetMapping("/material/delete")
    public String deleteMaterial(@RequestParam String tid, @RequestParam String itemid, RedirectAttributes ra) {
        try {
            dataService.deleteMaterialConsumption(tid, itemid);
            ra.addFlashAttribute("msg", "删除成功！");
        } catch (Exception e) {
            ra.addFlashAttribute("error", "删除失败：" + e.getMessage());
        }
        return "redirect:/manage";
    }
}
