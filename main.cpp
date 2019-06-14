/*
3公司员工培训系统
基本要求：
定义员工类，包含员工编号、姓名、出生日期、部门、职称、职位、性别、培训地点、培训时间、培训类别。
Number, Name, Date of Birth, Department, Title, Position, Gender, Place, Time and Category of Training
出生日期和培训时间要求定义成类，其中，培训时间应该包含起止日期。
保证输入到文件中的信息的准确性，例如出生日期和培训时间应考虑每月的起止日，例如闰年2月包括29天；员工编号必须唯一；性别只能为男、女。
功能要求：
1、增加员工培训信息；
2、可根据培训时间、员工编号、员工姓名、部门、职位等查询条件查询员工的培训信息；
3、修改员工的培训信息；
4、删除员工的培训信息；
5、可根据员工编号、部门、职称、培训时间对员工培训信息进行排序；
6、良好的人际交互界面、设计菜单实现功能选择、方便操作；
7、统计不同时段的培训员工数量。
8、实现员工培训信息的备份，也即将员工培训数据重新保存成另一份文件。
 */
#include <stdio.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cstring>
#define TTT "%-8s%-8s%-12s%-12s%-10s%-12s%-8s%-10s%-22s%-6s\n"
using namespace std;
class staff;
bool checkId(string,staff*);
int searchById(staff*);
void saveAll(staff*,char*);
int num = 0;//总数
char* ADDR = "t2.dat";
void showMenu(){//菜单
    cout << "----------0.Exit System" << endl
         << "----------1.Adding information" << endl
         << "----------2.List All information"<< endl
         << "----------3.Search information" << endl
         << "----------4.Updata information" << endl
         << "----------5.Delect information" << endl
         << "----------6.Sorting system" << endl//排序系统
         << "----------7.Statistical system" << endl//统计系统
         << "----------8.Backup file" << endl
         << "Please enter the number of the command you want to execute:" ;//备份文件
}
void showSearchMenu(){
    cout << "----------0.Exit System" << endl
         << "----------1.Search by id" << endl
         << "----------2.Search by name"<< endl
         << "----------3.Search by department" << endl
         << "----------4.Search by position" << endl
         << "----------5.Search by start time" << endl
         << "----------6.Search by end time" <<endl
         << "Please enter the number of the command you want to execute:";
}
//5、可根据员工编号、部门、职称、培训时间对员工培训信息进行排序；
void showSortMenu(){
    cout << "----------0.Exit System" << endl
         << "----------1.Sort by id" << endl
         << "----------2.Sort by department" << endl
         << "----------3.Sort by title" << endl
         << "----------4.Sort by start time" << endl
         << "----------5.Sort by end time" <<endl
         << "Please enter the number of the command you want to execute:";
}
bool isLyear(int year){//是否闰年
    if((year/4 == 0&& year/100 != 0) || year/400 ==0)
        return true;
    return false;
}
bool isBigmonth(int month){//是否大小月
    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return true;
        break;
    default:
        return false;
        break;
    }
}
class date{
    private:
        int year;
        int month;
        int day;
    public:
        date(){year = 0; month = 0; day = 0;}
        date(int a,int b,int c){
            year = a;
            month = b;
            day = c;
        }
        /*date(const date & a){
            year = a.getYear();
            month = a.getMonth();
            day = a.getDay();
        }*/
        void input(){
            int a,b,c;
            //cin>>a>>"-">>b>>"-">>c;
            while(1){
                cout<<"Please enter a date.Like this xxxx-x-x."<<endl;
                scanf("%d-%d-%d",&a,&b,&c);
                //cout<<a<<b<<c<<endl;
                //getchar();
                if(setYear(a) && setMonth(b) && setDay(c))
                    break;
                else cout<<"The date is illegal. Please re-enter it."<<endl;
                //getchar();
            }
            //cout<<beString()<<endl;
            /*while(1){
                cout<<"year:";
                cin>>a;
                if(setYear(a))
                    break;
                cout<<"The date is illegal. Please re-enter it."<<endl;
            }
            while(1){
                cout<<"month:";
                cin>>b;
                if(setMonth(b))
                    break;
                cout<<"The date is illegal. Please re-enter it."<<endl;
            }
            while(1){
                cout<<"day:";
                cin>>c;
                if(setDay(c))
                    break;
                cout<<"The date is illegal. Please re-enter it."<<endl;
            }*/
        }
        bool setYear(int y){
            if(y < 1)
                return false;
            year = y;
            return true;
        }
        int getYear(){return year;}
        bool setMonth(int y){
            if(y < 1 || y > 12)
                return false;
            month = y;
            return true;
        }
        int getMonth(){return month;}
        bool setDay(int y){
            if(y > 31 || y < 1)
                return false;
            if(month == 2 && !isLyear(year) && y > 28)
                return false;
            if(month == 2 && isLyear(year) && y > 29)
                return false;
            if(!isBigmonth(month) && y > 30)
                return false;   
            day = y;
            return true;
        }
        int getDay(){return day;}
        void toString(){
            //string re;
            char buf[20];
            sprintf(buf,"%d-%d-%d",year,month,day);
            //re = buf;
            cout<<buf;
        }
        bool operator>(date& a){
                if(year > a.getYear())
                    return true;
                else if(year < a.getYear())
                    return false;
                else if(month > a.getMonth())
                    return true;
                else if(month < a.getMonth())
                    return false;
                else if(day > a.getDay())
                    return true;
                else if(day < a.getDay())
                    return false;
        }
        bool isOne(date& a){
            if(year == a.getYear() && month == a.getMonth() && day == a.getDay())
                return true;
            else return false;
        }
        string beString(){
            char buf[20];
            sprintf(buf,"%d-%d-%d",year,month,day);
            return buf;
        }
};
class date_p{
    private:
        date start;
        date end;
    public:
        date_p(){}
        date_p(date& a,date& b):start(a),end(b){
        }
        void set(date& a,date& b){
            start = a;
            end = b;
        }
        void input(){
            cout<<"Please enter start time."<<endl;
            start.input();
            cout<<"Please enter end time."<<endl;
            end.input();
        }
        date getStarttime(){return start;}
        date getEndtime(){return end;}
        bool isInIt(date_p& a){
            if(a.getEndtime() > end && !(a.getStarttime() > start))
                return true;
            else return false;
        }
        void toString(){
            cout<<"starttime:";
            start.toString();
            cout<<endl;
            cout<<"endtime:";
            end.toString();
        }
        string beString(){
            return start.beString()+"/"+end.beString();
        }
};
class staff{
    private:
        char id[10];
        char name[10];
        date bir;
        char department[10];//部门
        char title[10];//职称
        char position[10];//职位
        bool isBoy;//性别
        char place[20];//地点
        date_p time;
        char category[20];//类别
    public:
        staff():bir(),time(){}
        string getId(){
            return id;
        }
        string getName(){
            return name;
        }
        string getDepartment(){
            return department;
        }
        string getTitle(){
            return title;
        }
        string getPosition(){
            return position;
        }
        date_p getTime(){
            return time;
        }
        void input(staff* sta){
            cout<<"Please enter ID"<<endl<<"id:";
            //cin>>id;
            //检查id是否相同，建议单独函数
            while (1)
            {
                cin>>id;
                if(checkId(id,sta))
                    break;
                else cout<<"Please enter other id!"<<endl;
            }
            cout<<"Please enter name"<<endl<<"name:";
            cin>>name;
            cout<<"Please enter birthday"<<endl<<"bir:";
            bir.input();
            cout<<"Please enter department"<<endl<<"department:";
            cin>>department;
            cout<<"Please enter title"<<endl<<"title:";
            cin>>title;
            cout<<"Please enter position"<<endl<<"position:";
            cin>>position;
            cout<<"Please enter gender(0:girl,1:boy)"<<endl<<"isBoy:";
            setIsBoy();
            cout<<"Please enter place"<<endl<<"place:";
            cin>>place;
            cout<<"Please enter Training time"<<endl<<"time:";
            setTime();
            cout<<"Please enter Training category"<<endl<<"category:";
            cin>>category;
        }
        void toString(){
            //string re;
            //cout<<"-------------------------"<<endl;
            cout<<"ID:"<<id<<endl;
            cout<<"name:"<<name<<endl;
            cout<<"birthday:";
            bir.toString();
            cout<<endl;
            cout<<"department:"<<department<<endl;
            cout<<"title:"<<title<<endl;
            cout<<"position:"<<position<<endl;
            string gender;
            if(isBoy)
                gender = "boy";
            else gender = "girl";
            cout<<"gender:"<<gender<<endl;
            cout<<"place:"<<place<<endl;
            cout<<"Training time"<<endl;
            time.toString();
            cout<<endl<<"Training category:"<<category<<endl;
            //return re;
        }
        void setIsBoy(){
            int i;
            while(1){
                cin>>i;
                if(i == 0||i == 1){
                    if(i == 0)
                        isBoy = false;
                    else if(i == 1)
                        isBoy = true;
                    break;
                }else cout<<"Please re-enter it use 0 or 1!"<<endl;
            }
        }
        void setTime(){
            date t1,t2;
            cout<<"Please enterr start time:";
            t1.input();
            cout<<"Please enter end time:";
            t2.input();
            time.set(t1,t2);
        }
        void printPer(){//有待改进
            string gender;
            if(isBoy)
                gender = "boy";
            else gender = "girl";
            printf(TTT,id,name
                    ,(char*)(bir.beString().data()),department,title,position,(char*)(gender.data()),place,(char*)(time.beString().data()),category);
        }
};
bool saveOne(staff *p,char* addr){//保存单个对象
    ofstream ofs(addr,ios::app|ios::binary);
    if(!ofs)
        return false;
    ofs.write((char*)p,sizeof(*p));
    ofs.close();
    num++;
    return true;
}
bool delectOne(staff* p){//删除单个
    //string id;
    cout << "Please enter id which one do you want to delect:" << endl;
    //cin >> id;
    int i = searchById(p);
    if(i == -1)
        return false;
    (p+i)->toString();
    cout<<"Do you want to delect it?(1 for yes,other for no):";
    int code;
    cin>>code;
    if(code != 1)
        return false;
    for(i;i < num-1;i++)
        *(p+i) = *(p+i+1);
    saveAll(p,ADDR);
    num--;
    return true;
}
int getNum(char* addr){//获取个数
    //num = 0;
    int i = 0;
    ifstream ifs(addr);
    if(!ifs)
        return 0;
    staff sta;
    while( ifs.read((char*)&sta,sizeof(sta)) )
        i++;
    ifs.close();
    return i;
}
void readAll(staff* p,char* addr){//将文件信息读入内存
    int i = 0;
    ifstream ifs(addr,ios::binary);
    for(i = 0;i < num;i++)
        {ifs.read((char*)p,sizeof(*p));p++;}
    ifs.close();
}
void saveAll(staff* p,char* addr){//将内存信息写入文件
    int i = 0;
    ofstream ofs(addr,ios::binary);//不用追加
    for(i = 0;i < num;i++)
        {ofs.write((char*)p,sizeof(*p));p++;}
    ofs.close();
}
void listInfo(staff* p){//暂时不写
    int i = 0;
    //Number, Name, Date of Birth, Department, Title, Position, Gender, Place, Time and Category of Training
    printf(TTT,"ID","Name"
                    ,"Birthday","Department","Title","Position","Gender","Place","Time of Training","Category");
    for(i = 0;i<num;i++)
        (p+i)->printPer();
    //p->toString();
    //system("pause");
}
int searchById(staff* sta){//成功返回数组下标，失败返回-1
    string id;
    cout<<"Pleas enter id:";
    cin>>id;
    for(int i = 0;i < num;i++,sta++)
    {
        if((id == (sta->getId())))
            return i;//因为id的唯一性
    }
    return -1;
    //system("pause");
}
bool searchByName(staff* sta){
    string name;
    bool re = false;
    cout<<"Please enter name:";
    cin>>name;
    for(int i = 0;i < num;i++,sta++){
        if((name == (sta->getName())))
            {sta->toString();re = true;}
    }
    return re;
}
bool searchByDepartment(staff* sta){
    string department;
    bool re = false;
    cout<<"Please enter department:";
    cin>>department;
    for(int i = 0;i < num;i++,sta++){
        if((department == (sta->getDepartment())))
            {sta->toString();re = true;}
    }
    return re;
}
bool searchByPosition(staff* sta){
    string position;
    bool re = false;
    cout<<"Please enter position:";
    cin>>position;
    for(int i = 0;i < num;i++,sta++){
        if((position == (sta->getPosition())))
            {sta->toString();re = true;}
    }
    return re;
}
bool searchByStartTime(staff* sta){
    bool re = false;
    date de;
    cout<<"Please enter start time:";
    de.input();
    for(int i = 0;i < num;i++,sta++){
        if((sta->getTime().getStarttime()).isOne(de))
            {sta->toString();re = true;}
    }
    return re;
}
bool searchByEndTime(staff* sta){
    bool re = false;
    date de;
    cout<<"Please enter end time:";
    de.input();
    for(int i = 0;i < num;i++,sta++){
        if((sta->getTime().getEndtime()).isOne(de))
            {sta->toString();re = true;}
    }
    return re;
}
bool statisticalInfo(staff* sta){//统计
    bool re = false;
    date_p te;
    te.input();
    for(int i = 0;i < num;i++,sta++){
        if( (sta->getTime()).isInIt(te) )
            {sta->toString();re = true;}
    }

    return re;
}
bool updataInfo(staff* p){
    cout << "Please enter id which one do you want to updata:" << endl;
    int i = searchById(p);
    if(i == -1)
        return false;
    (p+i)->toString();
    cout<<"Do you want to updata it?(1 for yes,other for no):";
    int code;
    cin>>code;
    if(code != 1)
        return false;
    staff tmp;
    tmp.input(p);
    *(p+i) = tmp;
    saveAll(p,ADDR);
    return true;
}
bool checkId(string id,staff* sta){
    for(int i = 0;i < num;i++,sta++)
    {
        if((id == (sta->getId())))
            return false;
    }
    return true;//没有找到，通过
}
bool backupFile(){//复制文件
    string addr;
    cout<<"Please enter new file name:";
    cin>>addr;
    //ifstream ifs(ADDR,ios::binary);
    //ofstream ofs(addr,ios::binary|ios::app);
    int i = getNum(ADDR);
    staff* sta = new staff[num];
    readAll(sta,ADDR);
    saveAll(sta,(char*)addr.data());
    /*//if(ifs == 0 || ofs == 0)
        //return false;
    char ch;
    while(ch != EOF)
        {ch = ifs.get();ofs.put(ch);}*/
    //ofs.close();
    //ifs.close();
    return true;
}
void cdSearchSystem(staff* p){
    int code,flag = 1;
    while(1){
        system("cls");
        showSearchMenu();
        cin >> code;
        switch (code)
        {
        case 0:
            flag = 0;
            break;
        case 1:{
            int i = searchById(p);
            if(-1 != i)
                (p+i)->toString();
            else cout<<"Don't find it!"<<endl;
            system("pause");
            break;
        }
        case 2:{
            if(!searchByName(p))
                cout<<"Don't find it!"<<endl;
            system("pause");
            break;
        }
        case 3:{
            if(!searchByDepartment(p))
                cout<<"Don't find it!"<<endl;
            system("pause");
            break;
        }
        case 4:{
            if(!searchByPosition(p))
                cout<<"Don't find it!"<<endl;
            system("pause");
            break;
        }
        case 5:{
            if(!searchByStartTime(p))
                cout<<"Don't find it!"<<endl;
            system("pause");
            break;
        }
        case 6:{
            if(!searchByEndTime(p))
                cout<<"Don't find it!"<<endl;
            system("pause");
            break;
        }
        default:
            break;
        }
        if(flag == 0)
            return;
    }
}
void sortById(staff* p){//冒泡排序
    //int min = 0;
    int i,j;
    for(i = 0;i < num;i++){
        for(j = 0;j < num-1-i;j++){
            if( (p+j)->getId() > (p+j+1)->getId()){
                staff tmp = *(p+j);
                *(p+j) = *(p+j+1);
                *(p+j+1) = tmp;
            }
        }
    }
}
void sortByDepartment(staff* p){//冒泡排序
    //int min = 0;
    int i,j;
    for(i = 0;i < num;i++){
        for(j = 0;j < num-1-i;j++){
            if( (p+j)->getDepartment() > (p+j+1)->getDepartment()){
                staff tmp = *(p+j);
                *(p+j) = *(p+j+1);
                *(p+j+1) = tmp;
            }
        }
    }
}
void sortByTitle(staff* p){//冒泡排序
    //int min = 0;
    int i,j;
    for(i = 0;i < num;i++){
        for(j = 0;j < num-1-i;j++){
            if( (p+j)->getTitle() > (p+j+1)->getTitle()){
                staff tmp = *(p+j);
                *(p+j) = *(p+j+1);
                *(p+j+1) = tmp;
            }
        }
    }
}
void sortByStartTime(staff* p){//冒泡排序
    //int min = 0;
    int i,j;
    for(i = 0;i < num-1;i++){
        for(j = 0;j < num-i-1;j++){
            date t1 = ((p+j)->getTime()).getStarttime();
            date t2 = ((p+j+1)->getTime()).getStarttime();
            //cout<<t1.beString()<<"vs"<<t2.beString();
            if( t1 > t2){
                staff tmp = *(p+j+1);
                *(p+j+1) = *(p+j);
                *(p+j) = tmp;
            }
        }
        //cout<<endl;
    }
}
void sortByEndTime(staff* p){//冒泡排序
    //int min = 0;
    int i,j;
    for(i = 0;i < num-1;i++){
        for(j = 0;j < num-1-i;j++){
            date t1 = ((p+j)->getTime()).getEndtime();
            date t2 = ((p+j+1)->getTime()).getEndtime();
            if( t1 > t2){
                staff tmp = *(p+j);
                *(p+j) = *(p+j+1);
                *(p+j+1) = tmp;
            }
        }
    }
}
void printAll(staff* p){
    for(int i = 0;i<num;i++)
        {cout<<"-----------"<<i+1<<"---------"<<endl;;(p+i)->toString();}
}
//5、可根据员工编号、部门、职称、培训时间对员工培训信息进行排序；
void cdSortSystem(staff* p){
    int code,flag = 1;
    while(1){
        system("cls");
        showSortMenu();
        cin >> code;
        //listInfo(p);
        switch (code)
        {
        case 0:
            flag = 0;
            break;
        case 1:{
            sortById(p);
            //printAll(p);
            listInfo(p);
            system("pause");
            break;
        }
        case 2:{
            sortByDepartment(p);
            //printAll(p);
            listInfo(p);
            system("pause");
            break;
        }
        case 3:{
            sortByTitle(p);
            //printAll(p);
            listInfo(p);
            system("pause");
            break;
        }
        case 4:{
            sortByStartTime(p);
            //printAll(p);
            listInfo(p);
            system("pause");
            break;
        }
        case 5:{
            sortByEndTime(p);
            //printAll(p);
            listInfo(p);
            system("pause");
            break;
        }
        default:
            break;
        }
        if(flag == 0)
            return;
    }
}
void test(staff* p = NULL){// == 比内容 strcmp比指针
    //listInfo(p);
    //cout<<("11"<"001");
    date t1(1999,12,31),t2(2000,1,1);
    //t1.input();
    //t2.input();
    //date a(2000,1,1),b(2020,1,1);
    //date_p te(t1,t2),te1(a,b);
    //te.set()
    cout<<(t1 > t2)<<endl;
    //cout<<(a>b)<<(a>c)<<(c>b);
    system("pause");
}
int main(){
    //listInfo();
    int check = 0,flag = 1;
    num = getNum(ADDR);
    staff* allsta = new staff[100];//动态申请节约空间,有待改进
    //readAll(allsta,ADDR);
    //test();
    while(1){
        system("cls");
        showMenu();
        cin >> check;
        switch (check)
        {
        case 0 :
            flag = 0;
            break;
        case 1 :{
            readAll(allsta,ADDR);
            staff p;
            p.input(allsta);//输入信息
            if(saveOne(&p,ADDR))
                cout<<"save successful!"<<endl;
            else cout<<"save false!"<<endl;
            system("pause");
            break;
        }
        case 2:{
            readAll(allsta,ADDR);
            listInfo(allsta);
            //printAll(allsta);
            system("pause");
            break;
        }
        case 3:{
            readAll(allsta,ADDR);
            cdSearchSystem(allsta);
            system("pause");
            break;
        }
        case 4:{
            readAll(allsta,ADDR);
            if(updataInfo(allsta))
                cout<<"Updata successful!"<<endl;
            else cout<<"Don't do it！"<<endl;
            system("pause");
            break;
        }
        case 5:{
            readAll(allsta,ADDR);
            if(delectOne(allsta))
                cout<<"Delect successful!"<<endl;
            else cout<<"Don't do it!"<<endl;
            system("pause");
            break;
        }
        case 6:
            readAll(allsta,ADDR);
            cdSortSystem(allsta);
            break;
        case 7:{//统计
            readAll(allsta,ADDR);
            if(!statisticalInfo(allsta))
                cout<<"Don't find it!"<<endl;
            system("pause");
            break;
        }
        case 8:{
            if(backupFile())
                cout<<"Backup successful!"<<endl;
            else cout<<"Backup failed!"<<endl;
            system("pause");
            break;
        }
        default :
            cout << "error!" <<endl;
            break;
        }
        if(flag == 0)
            break;
    }
    delete[] allsta;
    return 0;
}