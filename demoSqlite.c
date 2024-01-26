#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>

int main()
{
    sqlite3 *mydb = NULL;

    /* 打开数据库 : 如果数据库不存在, 那么就创建 */
    int ret = sqlite3_open("test.db", &mydb);
    if (ret != SQLITE_OK)
    {
        perror("sqlite open error");
        exit(-1);
    }

    #if 1
    char * errormsg = NULL;
    /* 删除表 : drop table + 表名 */
    const char *sql = "drop table user";
    ret = sqlite3_exec(mydb, sql, NULL, NULL, &errormsg);
    if (ret != SQLITE_OK)
    {
        printf("sqlite exec error:%s\n", errormsg);
        exit(-1);
    }
    #endif
    
    /* 
        创建一个表 
        create table 表名 (field1, field2, )
        create table user (id int primary key not NULL, age int not null, name text not null)
    */


    // char * errormsg = NULL;

#if 1
    sql = "create table if not exists user (id int primary key not NULL, age int not null, name text not null, address text not null)";
    ret = sqlite3_exec(mydb, sql, NULL, NULL, &errormsg);
    if (ret != SQLITE_OK)
    {
        printf("sqlite exec error:%s\n", errormsg);
        exit(-1);
    }

    sql = "insert into user values (1001, 10, 'zhangsan', 'jiangsu')";
    ret = sqlite3_exec(mydb, sql, NULL, NULL, &errormsg);
    if (ret != SQLITE_OK)
    {
        printf("sqlite exec error:%s\n", errormsg);
        exit(-1);
    }

    sql = "insert into user values (1002, 20, 'lisi', 'zhejiang')";
    ret = sqlite3_exec(mydb, sql, NULL, NULL, &errormsg);
    if (ret != SQLITE_OK)
    {
        printf("sqlite exec error:%s\n", errormsg);
        exit(-1);
    }

    sql = "insert into user values (1003, 30, 'wangwu', 'hunan')";
    ret = sqlite3_exec(mydb, sql, NULL, NULL, &errormsg);
    if (ret != SQLITE_OK)
    {
        printf("sqlite exec error:%s\n", errormsg);
        exit(-1);
    }
#endif

    #if 0
    /* 新增一列address的属性 */
    sql = "alter table user add address text";
    ret = sqlite3_exec(mydb, sql, NULL, NULL, &errormsg);
    if (ret != SQLITE_OK)
    {
        printf("sqlite exec error:%s\n", errormsg);
        exit(-1);
    }
    #endif

    #if 0
    /* 删除一列age的属性 */
    sql = "alter table user drop age";
    ret = sqlite3_exec(mydb, sql, NULL, NULL, &errormsg);
    if (ret != SQLITE_OK)
    {
        printf("sqlite exec error:%s\n", errormsg);
        exit(-1);
    }
    #endif

    #if 0
    /* 更改列的属性 从text文本字符串改成int */
    sql = "alter table user alter column address int";
    ret = sqlite3_exec(mydb, sql, NULL, NULL, &errormsg);
    if (ret != SQLITE_OK)
    {
        printf("sqlite exec error:%s\n", errormsg);
        exit(-1);
    }
    #endif

   

    /* 查询数据库 */
    /* 
        sql: select * from user;
    */
    sql = "select id, age from user";

    char ** result = NULL;
    int row = 0;
    int column = 0;
    ret = sqlite3_get_table(mydb, sql, &result, &row, &column, &errormsg);
    if (ret != SQLITE_OK)
    {
        printf("sqlite3_get_table error:%s\n", errormsg);
        exit(-1);
    }
    printf("row:%d,\t cloumn:%d\n", row, column);

    /* 查询数据库 : 每次读取一行 */
    for (int idx = 0; idx <= row; idx++)
    {
        for (int jdx = 0; jdx < column; jdx++)
        {
            printf("%s\t", result[idx * column + jdx]);
        }
        printf("\n");
    }

    #if 1
    /* 模糊匹配 */
    sql = "select name from user where address LIKE 'jiang%' ";
    ret = sqlite3_get_table(mydb, sql, &result, &row, &column, &errormsg);
    if (ret != SQLITE_OK)
    {
        printf("sqlite3_get_table error:%s\n", errormsg);
        exit(-1);
    }
    printf("row:%d,\t cloumn:%d\n", row, column);

    /* 查询数据库 : 每次读取一行 */
    for (int idx = 0; idx <= row; idx++)
    {
        for (int jdx = 0; jdx < column; jdx++)
        {
            printf("%s\t", result[idx * column + jdx]);
        }
        printf("\n");
    }
    #endif

    #if 1
    /* order By */
    sql = "select name from user order by age desc";
    ret = sqlite3_get_table(mydb, sql, &result, &row, &column, &errormsg);
    if (ret != SQLITE_OK)
    {
        printf("sqlite3_get_table error:%s\n", errormsg);
        exit(-1);
    }
    printf("row:%d,\t cloumn:%d\n", row, column);

    /* 查询数据库 : 每次读取一行 */
    for (int idx = 0; idx <= row; idx++)
    {
        for (int jdx = 0; jdx < column; jdx++)
        {
            printf("%s\t", result[idx * column + jdx]);
        }
        printf("\n");
    }
    #endif

    /* 更新数据表数据 */
    /* sql: update + 表名  set field1 = value1 where [condition] */

    sql = "update user set age = 15 where name = 'zhangsan'";
    ret = sqlite3_exec(mydb, sql, NULL, NULL, &errormsg);
    if (ret != SQLITE_OK)
    {
        printf("sqlite exec error:%s\n", errormsg);
        exit(-1);
    }


    #if 0
    /* 删除表 : drop table + 表名 */
    sql = "drop table user";
    ret = sqlite3_exec(mydb, sql, NULL, NULL, &errormsg);
    if (ret != SQLITE_OK)
    {
        printf("sqlite exec error:%s\n", errormsg);
        exit(-1);
    }
    #endif

    /* 关闭数据库 */
    sqlite3_close(mydb);
    return 0;
}