#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
 
void get_format_time_string(char *str_time) //获取格式化时间
{
    time_t now;
    struct tm *tm_now;
    char datetime[128];
    time(&now);
    tm_now = localtime(&now);
    strftime(datetime, 128, "%Y/%m/%d", tm_now);
//    printf("now datetime : %s\n", datetime);
    strcpy(str_time, datetime);
}
 
int main(int argc,char** argv)
{
 
    char date_now[128] = {0};
    get_format_time_string(date_now);
    char cmd[128] = {0};
    char* date_fmt = "date %s";
    if(argc>=2){
        sprintf(cmd,date_fmt, argv[1]);
    } else{
        sprintf(cmd,date_fmt, "2021/01/01");
    }
    //将系统时间回调
    system(cmd);
    //启动程序
    if(argc >= 3){
        sprintf(cmd,"start %s", argv[2]);
        system(cmd);
    } else {
        system("start Typora.exe");
    }
    sprintf(cmd,"date %s",date_now);
    _sleep(3000);
    //恢复系统时间
    system(cmd);
    printf("%s", cmd);
//    printf("timestamp:%lld, format time:%s", curr_time, date_now);
    return 0;
}