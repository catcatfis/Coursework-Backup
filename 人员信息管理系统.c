#include <stdio.h>
#include <string.h>
#define MAX_PEOPLE 100
typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
    char birthDate[20];
    char address[100];
    float salary;
} Person;
Person people[MAX_PEOPLE];
int peopleCount = 0;
void addPerson() {
    if (peopleCount >= MAX_PEOPLE) {
        printf("人员已满，无法添加更多人员。\n");
        return;
    }
    Person newPerson;
    printf("输入人员ID: ");
    scanf("%d", &newPerson.id);
    printf("输入姓名: ");
    scanf("%s", newPerson.name);
    printf("输入年龄: ");
    scanf("%d", &newPerson.age);
    printf("输入性别: ");
    scanf("%s", newPerson.gender);
    printf("输入出生日期(YYYY-MM-DD): ");
    scanf("%s", newPerson.birthDate);
    printf("输入地址: ");
    scanf("%s", newPerson.address);
    printf("输入工资: ");
    scanf("%f", &newPerson.salary);
    people[peopleCount++] = newPerson;
    printf("人员添加成功。\n");
}
void modifyPerson() {
    int id;
    printf("输入要修改的人员ID: ");
    scanf("%d", &id);
    for (int i = 0; i < peopleCount; i++) {
        if (people[i].id == id) {
            printf("输入新的姓名: ");
            scanf("%s", people[i].name);
            printf("输入新的年龄: ");
            scanf("%d", &people[i].age);
            printf("输入新的性别: ");
            scanf("%s", people[i].gender);
            printf("输入新的出生日期(YYYY-MM-DD): ");
            scanf("%s", people[i].birthDate);
            printf("输入新的地址: ");
            scanf("%s", people[i].address);
            printf("输入新的工资: ");
            scanf("%f", &people[i].salary);
            printf("人员信息修改成功。\n");
            return;
        }
    }
    printf("未找到对应ID的人员。\n");
}
void deletePerson() {
    int id;
    printf("输入要删除的人员ID: ");
    scanf("%d", &id);
    for (int i = 0; i < peopleCount; i++) {
        if (people[i].id == id) {
            for (int j = i; j < peopleCount - 1; j++) {
                people[j] = people[j + 1];
            }
            peopleCount--;
            printf("人员删除成功。\n");
            return;
        }
    }
    printf("未找到对应ID的人员。\n");
}
void queryPerson() {
    int id;
    printf("输入要查询的人员ID: ");
    scanf("%d", &id);
    for (int i = 0; i < peopleCount; i++) {
        if (people[i].id == id) {
            printf("ID: %d, 姓名: %s, 年龄: %d, 性别: %s, 出生日期: %s, 地址: %s, 工资: %.2f\n",
                   people[i].id, people[i].name, people[i].age, people[i].gender,
                   people[i].birthDate, people[i].address, people[i].salary);
            return;
        }
    }
    printf("未找到对应ID的人员。\n");
}
void displayPeople() {
    if (peopleCount == 0) {
        printf("当前无人员信息。\n");
        return;
    }
    for (int i = 0; i < peopleCount; i++) {
        printf("ID: %d, 姓名: %s, 年龄: %d, 性别: %s, 出生日期: %s, 地址: %s, 工资: %.2f\n",
               people[i].id, people[i].name, people[i].age, people[i].gender,
               people[i].birthDate, people[i].address, people[i].salary);
    }
}
int main() {
    int choice;
    while (1) {
        printf("1. 增加人员\n2. 修改人员\n3. 删除人员\n4. 查询人员\n5. 显示所有人员\n0. 退出\n");
        printf("请选择操作: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                addPerson();
                break;
            case 2:
                modifyPerson();
                break;
            case 3:
                deletePerson();
                break;
            case 4:
                queryPerson();
                break;
            case 5:
                displayPeople();
                break;
            case 0:
                return 0;
            default:
                printf("无效的选择。\n");
        }
    }
    return 0;
}
