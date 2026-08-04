package sjk.sjksj.entity;

import lombok.Data;

@Data
public class MaterialConsumption {
    private String tid;
    private String itemid;
    private Integer quantity;
    private Double price;
}
