#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_

#pragma warning(disable:4786)


// 现在cdkey功能有两种。第一种：一个cdkey只可以被玩家使用一次，使用之后这个cdkey就无效。第二种：一个cdkey可以重复被玩家使用，但是每个玩家只能参与一次该活动
// 可选字母组合
// static char LETTER[] = {'a','b','c','d','e','f','g','h','i','j','k','m','n','p','q','r','s','t','u','v','w','x','y','z',
// 						'A','B','C','D','E','F','G','H','J','K','L','M','N','P','Q','R','S','T','U','V','W','X','Y','Z','\0'};

// 数字长度默认日期年月日天时组成
static const int PREFIX_LEN = 3; // CDKEY前缀长度
static const int DIGIT_LEN = 8;
static const int STR_MIN_LEN = PREFIX_LEN + DIGIT_LEN + 1;
static const int STR_MAX_LEN = 32;

static char LETTER[] = {'a','b','c','d','e','f','g','h','i','j','k','m','n','p','q','r','s','t','u','v','w','x','y','z','\0'};

// 第一种前3位前缀
static char LETTER_ONLYPREFIX[][PREFIX_LEN+1] = {"1yj","2yj","3yj","4yj","5yj","6yj","7yj","8yj","9yj","yj1","yj2","yj3","yj4","yj5","yj6","yj7","yj8","yj9"};

static const char* SAVE_FILE = "cdkey.txt";
static const char* SQL_SAVE_FILE = "cdkey_outsql.txt";
static const char* SQL_READ_FILE = "cdkey_insql.txt";

#endif // _TYPEDEF_H_
