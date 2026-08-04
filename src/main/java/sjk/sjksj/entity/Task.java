package sjk.sjksj.entity;

import lombok.Data;
import java.time.LocalDate;

@Data
public class Task {
    private String tid;
    private String dpid;
    private String owid;
    private Double budgetamount;
    private String budgeter;
    private LocalDate budgetdate;
    private LocalDate startdate;
    private LocalDate enddate;
    private String cname;
    private String constructionContent;
    private Double materialcost;
    private Double laborcost;
    private Double equipmentcost;
    private Double othercost;
    private Double settlementamount;
    private String settlementer;
    private LocalDate settlementdate;
    private Double amountcredited;
    private String amountcrediter;
    private LocalDate amountcreditedate;
}
