/*template_test.h*/
#ifndef TEMPLATE_TEST_H
#define TEMPLATE_TEST_H

//������A������ʱ����ӡ��־
#define CHECK_CONDITION(A) do\
{\
	if (!(A)) {\
		cout <<"<Error>:" <<__FILE__ << ": " << __FUNCTION__ << ": " << __LINE__ << endl; \
		return; \
	}\
}while (0)

#define UINT32 unsigned int
#define UINT16 unsigned short
#define UINT8 unsigned char

#endif