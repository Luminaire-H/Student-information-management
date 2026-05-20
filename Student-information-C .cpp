#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Student {
    struct Student *prior;
    int id;
    char name[16];
    int gender;          // 1:男 2:女
    struct Student *next;
} student;

// 创建链表（带哑节点的双向循环链表）
student *creatlist(int n) {
    student *L = (student*)malloc(sizeof(student));
    if (NULL == L) {
        printf("malloc failed\n");
        return NULL;
    }
    // 初始化哑节点，自己指向自己
    L->next = L;
    L->prior = L;

    student *r = L;  // r指向当前最后一个节点（初始为哑节点）

    for (int i = 0; i < n; i++) {
        student *p = (student*)malloc(sizeof(student));
        if (NULL == p) {
            printf("malloc failed\n");
            return NULL;
        }
        // 尾插法：插入到 r 和 L 之间
        p->next = L;
        p->prior = r;
        r->next = p;
        L->prior = p;
        r = p;

        printf("请分别输入学生id，姓名，性别(性别为男输入1，性别为女输入2)。\n");
        scanf("%d %s %d", &p->id, p->name, &p->gender);
    }
    return L;
}

// 按学号查找
student *searchList(int id, student *L) {
    student *cur = L->next;  // 从第一个真实节点开始
    while (cur != L) {
        if (cur->id == id) {
            printf("学号：%d 姓名：%s 性别：%d\n", cur->id, cur->name, cur->gender);
            return cur;
        }
        cur = cur->next;
    }
    printf("查找失败，无此学生！\n");
    return NULL;
}

// 按姓名删除（修复了原代码中的边界处理）
void delete_student(student **L, char *delete_name) {
    if (*L == NULL || (*L)->next == *L) {
        printf("链表为空，无学生可删除。\n");
        return;
    }

    student *cur = (*L)->next;
    while (cur != *L) {
        if (strcmp(delete_name, cur->name) == 0) {
            // 将cur从链表中移除
            cur->prior->next = cur->next;
            cur->next->prior = cur->prior;
            free(cur);
            printf("学生信息删除成功。\n");
            return;
        }
        cur = cur->next;
    }
    printf("未找到名为 %s 的学生信息，无法删除。\n", delete_name);
}

// 输出所有学生
void output_students(student *L) {
    if (L == NULL || L->next == L) {
        printf("暂无学生数据。\n");
        return;
    }
    student *cur = L->next;
    printf("学号\t姓名\t性别\n");
    while (cur != L) {
        printf("%d\t%s\t%d\n", cur->id, cur->name, cur->gender);
        cur = cur->next;
    }
}

// 释放整个链表（可选，防止内存泄漏）
void free_list(student *L) {
    if (L == NULL) return;
    student *cur = L->next;
    while (cur != L) {
        student *tmp = cur;
        cur = cur->next;
        free(tmp);
    }
    free(L);
}

int main() {
    int choice, n;
    student *L = NULL;

    while (1) {
        printf("\n请选择操作:\n");
        printf("*****************************************************\n");
        printf("*                       1 插入                      *\n");
        printf("*                       2 查找                      *\n");
        printf("*                       3 删除                      *\n");
        printf("*                       4 输出                      *\n");
        printf("*                       5 退出                      *\n");
        printf("*****************************************************\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("请输入学生数量：");
                scanf("%d", &n);
                L = creatlist(n);
                break;
            case 2:
                if (L == NULL || L->next == L) {
                    printf("暂无学生数据，请先插入学生。\n");
                } else {
                    printf("请输入要查找的学生id：");
                    scanf("%d", &n);
                    searchList(n, L);
                }
                break;
            case 3:
                if (L == NULL || L->next == L) {
                    printf("暂无学生数据，无法删除。\n");
                } else {
                    char delete_name[16];
                    printf("请输入要删除的学生姓名：");
                    scanf("%s", delete_name);
                    delete_student(&L, delete_name);
                }
                break;
            case 4:
                if (L == NULL || L->next == L) {
                    printf("暂无学生数据。\n");
                } else {
                    output_students(L);
                }
                break;
            case 5:
                free_list(L);   // 退出前释放内存
                printf("已退出系统。\n");
                return 0;
            default:
                printf("无效输入，请重新选择。\n");
        }
    }
    return 0;
}