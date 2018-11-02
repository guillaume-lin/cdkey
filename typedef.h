#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_

#pragma warning(disable:4786)


// ����cdkey���������֡���һ�֣�һ��cdkeyֻ���Ա����ʹ��һ�Σ�ʹ��֮�����cdkey����Ч���ڶ��֣�һ��cdkey�����ظ������ʹ�ã�����ÿ�����ֻ�ܲ���һ�θû
// ��ѡ��ĸ���
// static char LETTER[] = {'a','b','c','d','e','f','g','h','i','j','k','m','n','p','q','r','s','t','u','v','w','x','y','z',
// 						'A','B','C','D','E','F','G','H','J','K','L','M','N','P','Q','R','S','T','U','V','W','X','Y','Z','\0'};

// ���ֳ���Ĭ��������������ʱ���
static const int PREFIX_LEN = 3; // CDKEYǰ׺����
static const int DIGIT_LEN = 8;
static const int STR_MIN_LEN = PREFIX_LEN + DIGIT_LEN + 1;
static const int STR_MAX_LEN = 32;

static char LETTER[] = {'a','b','c','d','e','f','g','h','i','j','k','m','n','p','q','r','s','t','u','v','w','x','y','z','\0'};

// ��һ��ǰ3λǰ׺
static char LETTER_ONLYPREFIX[][PREFIX_LEN+1] = {"1yj","2yj","3yj","4yj","5yj","6yj","7yj","8yj","9yj","yj1","yj2","yj3","yj4","yj5","yj6","yj7","yj8","yj9"};

static const char* SAVE_FILE = "cdkey.txt";
static const char* SQL_SAVE_FILE = "cdkey_outsql.txt";
static const char* SQL_READ_FILE = "cdkey_insql.txt";

#endif // _TYPEDEF_H_
