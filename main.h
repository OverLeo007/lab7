//
// Created by leva on 25.05.2022.
//

#ifndef LAB7_MAIN_H
#define LAB7_MAIN_H


typedef enum {
    ADD_EMPLOYEE = 1,
    ADD_OBJECT,
    PRINT_EMPLOYEES,
    PRINT_OBJECTS,
    PICK_OBJECT,
    PICK_EMPLOYEE,
    ADD_CONNECTION,
    EXIT
} main_menu_enum;

typedef struct {
    char *name;
    int s_acc_lvl;
    char *address;
} object;

typedef struct {
    char *name;
    int b_year;
    char gender;
    int access_lvl;
} employee;

typedef struct _ObjNode {
    object value;
    int conn_size;
    struct _EmpNode **connections;
    struct _ObjNode *next;
    struct _ObjNode *prev;
} ONode;

typedef struct _ObjDblLinkedList {
    size_t size;
    ONode *head;
    ONode *tail;
} ODblLinkedList;

typedef struct _EmpNode {
    employee value;
    int conn_size;
    struct _ObjNode **connections;
    struct _EmpNode *next;
    struct _EmpNode *prev;
} ENode;

typedef struct _EmpDblLinkedList {
    size_t size;
    ENode *head;
    ENode *tail;
} EDblLinkedList;


/*!
 * \brief создание списка объектов
 * \return созданный пустой двусвязный список объектов
 */
ODblLinkedList *create_odblLinkedList();


/*!
 * \brief удаляет список объектов, очищая память занятую им
 * \details последовательно удаляет каждую ноду,
 * также очищая память занятую ее value
 * \param list список для удаления
 */
void delete_odblLinkedList(ODblLinkedList **list);


/*!
 * \brief создание списка сотрудников
 * \return созданный пустой двусвязный список сотрудников
 */
EDblLinkedList *create_edblLinkedList();


/*!
 * \brief удаляет список сотрудников, очищая память занятую им
 * \details последовательно удаляет каждую ноду,
 * также очищая память занятую ее value
 * \param list список для удаления
 */
void delete_edblLinkedList(EDblLinkedList **list);


/*!
 * \brief добавляет ноду в список объектов по значениям value
 * \details создает экземпляр object и заполняет его входными значениями,
 * добавляет в список ноду, value которой - экземпляр object
 * \param name название объекта
 * \param s_lvl уровень секретности объекта
 * \param address адрес объекта
 * \param list список объектов в который добавляем ноду
 */
void add_object(char *name, int s_lvl, char *address, ODblLinkedList *list);


/*!
 * \brief добавляет ноду в список сотрудников по значениям value
 * \details создает экземпляр employee и заполняет его входными значениями,
 * добавляет в список ноду, value которой - экземпляр employee
 * \param name имя сотрудника
 * \param b_year год рождения сотрудника
 * \param gender пол сотрудника
 * \param access_lvl уровень допуска сотрудника
 * \param list список сотрудников в который добавляем ноду
 */
void add_employee(char *name, int b_year, char gender,
                  int access_lvl,
                  EDblLinkedList *list);


/*!
 * \brief возвращает ноду из списка объектов по индексу
 * \param list список из которого хотим получить ноду
 * \param index индекс ноды в списке
 * \return нода, индекс которой был на входе
 */
ONode *get_object(ODblLinkedList *list, size_t index);


/*!
 * \brief возвращает ноду из списка сотрудников по индексу
 * \param list список из которого хотим получить ноду
 * \param index индекс ноды в списке
 * \return нода, индекс которой был на входе
 */
ENode *get_employee(EDblLinkedList *list, size_t index);


/*!
 * \brief соединяет ноды сотрудника и объекта
 * \details добавляет в список connections
 * ноды сотрудника ноду объекта и наоборот
 * \param obj нода объекта
 * \param emp нода сотрудника
 * \return 0 - соединено корректно
 * \return 1 - соеднинения не произошло
 */
int connect_nodes(ONode *obj, ENode *emp);


/*!
 * \brief выводит объект
 * \details выводит объект выводя либо допущенных
 * на него сотрудников либо их имена
 * \param node объект для вывода
 * \param num его номер в списке
 * \param is_conns true - выводит имена сотрудников,
 *                 false - выводит их количество
 */
void print_object(ONode *node, int num, bool is_conns);


/*!
 * \brief выводит все объекта из списка
 * \param list список содержащий объекты для вывода
 */
void print_objects(ODblLinkedList *list);


/*!
 * \brief выводит сотрудника
 * \details выводит сотрудника выводя либо количестов доступных
 * ему объектов либо их названия
 * \param node сотрудник для вывода
 * \param num его номер в списке
 * \param is_conns true - выводит название объектов,
 *                 false - выводит их количество
 */
void print_employee(ENode *node, int num, bool is_conns);

/*!
 * \brief выводит всех сотрудников из списка
 * \param list список содержащий сотрудников для вывода
 */
void print_employees(EDblLinkedList *list);


#endif //LAB7_MAIN_H
