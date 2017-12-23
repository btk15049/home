constexpr int MIN = 60;
constexpr int HOUR = 3600;
constexpr int DAY = 86400;
constexpr int YEAR = 31536000;
constexpr int days[2][13] = {
    {0,31,28,31,30,31,30,31,31,30,31,30,31},//not uruu
    {0,31,29,31,30,31,30,31,31,30,31,30,31} //yes uruu
};
bool isuruu(int year){
    return !((year % 100 ==0 && year % 400 != 0) || year % 4 != 0);
}
