#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "inoutput_funcs.h"
#include "main.h"


int main() {
    EDblLinkedList *employees = create_edblLinkedList();
    ODblLinkedList *objects = create_odblLinkedList();

    system("chcp 65001 > nul");

    char emp_names[5][10] = {"Klef", "Bright",
                             "Kondraki", "Gears",
                             "O5-1"};

    char obj_names[6][10] = {"SCP-076",
                             "SCP-058",
                             "SCP-169",
                             "SCP-2935",
                             "SCP-001"};
    char obj_address[6][20] = {"Zone 1",
                               "Zone 2",
                               "Zone 3",
                               "Zone 4",
                               "Zone 0"};
    for (int i = 0; i < 5; i++) {
        char gender;
        if (i < 2) gender = 'F'; else gender = 'M';
        add_employee(emp_names[i], 1980 + i, gender, i + 1, employees);
        add_object(obj_names[i], i + 1, obj_address[i], objects);
    }


    while (true) {
        puts("1. Добавить сотрудника");
        puts("2. Добавить объект");
        puts("3. Вывести всех сотрудников");
        puts("4. Вывести все объекты");
        puts("5. Вывести объект и всех допущенных на него сотрудников");
        puts("6. Вывести сотрудника и все доступные ему объекты");
        puts("7. Добавить сотрудника на объект");
        puts("8. Выйти");
        int menu_variant = input_int();
        switch (menu_variant) {
            case ADD_EMPLOYEE:
                puts("Введите имя сотрудника:");
                char *name = input_string();
                if (name[0] == '\0') {
                    puts("Некорректное имя!");
                    break;
                }
                puts("Введите год рождения сотрудника:");
                int b_year = input_int();
                if (b_year == -1) {
                    puts("Некорректная длина!");
                    break;
                }
                puts("Введите пол сотрудника (M, F)");
                char gender = (char) getc(stdin);
                fflush(stdin);
                if (gender != 'M' && gender != 'F') {
                    puts("Некорректно введен пол!");
                    break;
                }
                puts("Введите уровень допуска сотрудника:");
                int acc_lvl = input_int();
                if (acc_lvl == -1) {
                    puts("Некорректный уровень допуска!");
                    break;
                }
                add_employee(name, b_year, gender, acc_lvl, employees);
                puts("Сотрудник успешно добавлен");

                break;
            case ADD_OBJECT:
                puts("Введите название объекта:");
                char *o_name = input_string();
                if (o_name[0] == '\0') {
                    puts("Некорректное название!");
                    break;
                }
                puts("Введите уровень секретности объекта:");
                int o_acc_lvl = input_int();
                if (o_acc_lvl == -1) {
                    puts("Некорректный уровень допуска!");
                    break;
                }
                puts("Введите адрес объекта:");
                char *o_address = input_string();
                if (o_address[0] == '\0') {
                    puts("Некорректный адрес!");
                    break;
                }
                add_object(o_name, o_acc_lvl, o_address, objects);
                puts("Объект успешно добавлен");

                break;
            case PRINT_EMPLOYEES:
                print_employees(employees);

                break;
            case PRINT_OBJECTS:
                print_objects(objects);

                break;
            case PICK_OBJECT: {
                puts("Введите номер объекта:");
                int obj_num = input_int() - 1;
                ONode *piked_obj = get_object(objects, obj_num);
                if (piked_obj == NULL) {
                    puts("Некорректный номер объекта!");
                    break;
                }
                print_object(piked_obj, obj_num, true);
            }
                break;
            case PICK_EMPLOYEE: {
                puts("Введите номер сотрудника:");
                int emp_num = input_int() - 1;
                ENode *piked_emp = get_employee(employees, emp_num);
                if (piked_emp == NULL) {
                    puts("Некорректный номер объекта!");
                    break;
                }
                print_employee(piked_emp, emp_num, true);
            }

                break;
            case ADD_CONNECTION:{
                puts("Введите номер сотрудника:");
                int emp_num = input_int() - 1;
                ENode *piked_emp = get_employee(employees, emp_num);
                if (piked_emp == NULL) {
                    puts("Некорректный номер объекта!");
                    break;
                }
                puts("Введите номер объекта:");
                int obj_num = input_int() - 1;
                ONode *piked_obj = get_object(objects, obj_num);
                if (piked_obj == NULL) {
                    puts("Некорректный номер объекта!");
                    break;
                }
                if (!connect_nodes(piked_obj, piked_emp))
                puts("Сотрудник добавлен на объект");
            }
                break;
            case EXIT:
                delete_edblLinkedList(&employees);
                delete_odblLinkedList(&objects);
                return 0;

            default:
                puts("Такого варианта выбора нет");

                break;
        }
    }
}


ODblLinkedList *create_odblLinkedList() {
    ODblLinkedList *tmp = (ODblLinkedList *) malloc(sizeof(ODblLinkedList));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;

    return tmp;
}


//TODO Сделать очистку всех полей
void delete_odblLinkedList(ODblLinkedList **list) {
    ONode *tmp = (*list)->head;
    ONode *next = NULL;
    while (tmp) {
        next = tmp->next;
        free(tmp->connections);
//        free((tmp->value).name);
//        free((tmp->value).address);
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}


EDblLinkedList *create_edblLinkedList() {
    EDblLinkedList *tmp = (EDblLinkedList *) malloc(sizeof(EDblLinkedList));
    tmp->size = 0;
    tmp->head = tmp->tail = NULL;

    return tmp;
}


//TODO Сделать очистку всех полей
void delete_edblLinkedList(EDblLinkedList **list) {
    ENode *tmp = (*list)->head;
    ENode *next = NULL;
    while (tmp) {
        next = tmp->next;
//        free(tmp->connections);
//        free((tmp->value).name);
        free(tmp);
        tmp = next;
    }
    free(*list);
    (*list) = NULL;
}


void add_object(char *name, int s_lvl, char *address, ODblLinkedList *list) {
    object tmp_object;
    tmp_object.name = name;
    tmp_object.s_acc_lvl = s_lvl;
    tmp_object.address = address;


    ONode *tmp = (ONode *) malloc(sizeof(ONode));

    tmp->value = tmp_object;
    tmp->next = NULL;
    tmp->prev = list->tail;
    tmp->conn_size = 0;
    tmp->connections = (ENode **) malloc(1000 * sizeof(ENode *));

    if (list->tail) {
        list->tail->next = tmp;
    }
    list->tail = tmp;

    if (list->head == NULL) {
        list->head = tmp;
    }
    list->size++;
}


void add_employee(char *name, int b_year, char gender,
                  int access_lvl,
                  EDblLinkedList *list) {
    employee tmp_employee;
    tmp_employee.name = name;
    tmp_employee.b_year = b_year;
    tmp_employee.gender = gender;
    tmp_employee.access_lvl = access_lvl;

    ENode *tmp = (ENode *) malloc(sizeof(ENode));

    tmp->value = tmp_employee;
    tmp->next = NULL;
    tmp->prev = list->tail;
    tmp->conn_size = 0;
    tmp->connections = (ONode **) malloc(1000 * sizeof(ONode *));

    if (list->tail) {
        list->tail->next = tmp;
    }
    list->tail = tmp;

    if (list->head == NULL) {
        list->head = tmp;
    }
    list->size++;
}

ONode *get_object(ODblLinkedList *list, size_t index) {
    ONode *tmp = list->head;
    size_t i = 0;

    while (tmp && i < index) {
        tmp = tmp->next;
        i++;
    }

    return tmp;
}


ENode *get_employee(EDblLinkedList *list, size_t index) {
    ENode *tmp = list->head;
    size_t i = 0;

    while (tmp && i < index) {
        tmp = tmp->next;
        i++;
    }

    return tmp;
}


int connect_nodes(ONode *obj, ENode *emp) {
    if ((obj->value).s_acc_lvl > (emp->value).access_lvl) {
        puts("Сотруднику не хватает уровня допуска для добавления на объект");
        return 1;
    }
    if (obj->conn_size >= 999) {
        puts("Количество человек на объекте максимально");
    }
    if (emp->conn_size >= 999) {
        puts("Количество объектов на которое допущен сотрудник максимально");
    }
    obj->connections[obj->conn_size++] = emp;
    emp->connections[emp->conn_size++] = obj;
    return 0;
}


void print_object(ONode *node, int num, bool is_conns) {
    object obj = node->value;
    printf("Объект №%d:\n", num + 1);
    printf("\t%s\n", obj.name);
    printf("\tУровень секретности: %d\n", obj.s_acc_lvl);
    printf("\tАдрес: %s\n", obj.address);
    if (node->conn_size == 0){
        puts("\tНи один сотрудник не допущен на объект");
        return;
    }
    if (is_conns) {
        puts("\tСотрудники на объекте:");
        ENode **emps = node->connections;
        for (int i = 0; i < node->conn_size; i++) {
            printf("\t\t%s\n", (emps[i]->value).name);
        }
    } else {
        printf("\tСотрудников на объекте: %d\n", node->conn_size);
    }
}

void print_objects(ODblLinkedList *list) {
    if (list->size == 0) {
        puts("Не добавлено ни одного объекта");
        return;
    }
    ONode *tmp = list->head;
    int i = 0;

    while (tmp) {
        print_object(tmp, i, false);
        tmp = tmp->next;
        ++i;
    }
}


void print_employee(ENode *node, int num, bool is_conns) {
    employee emp = node->value;
    printf("Сотрудник №%d:\n", num + 1);
    printf("\t%s\n", emp.name);
    printf("\tГод рождения: %d\n", emp.b_year);
    printf("\tУровень допуска: %d\n", emp.access_lvl);
    printf("\tПол: %c\n", emp.gender);
    if (node->conn_size == 0){
        puts("\tСотрудник не допущен ни на один объект");
        return;
    }
    if (is_conns) {
        puts("\tДопущен на объекты:");
        ONode **objs = node->connections;
        for (int i = 0; i < node->conn_size; i++) {
            printf("\t\t%s\n", (objs[i]->value).name);
        }
    } else {
        printf("\tИмеет доступ к %d объектам\n", node->conn_size);
    }
}


void print_employees(EDblLinkedList *list) {
    if (list->size == 0) {
        puts("Не добавлено ни одного сотрудника");
        return;
    }
    ENode *tmp = list->head;
    int i = 0;

    while (tmp) {
        print_employee(tmp, i, false);
        tmp = tmp->next;
        ++i;
    }
}
