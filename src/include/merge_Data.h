#ifndef URLTOPN_MERGE_DATA_H
#define URLTOPN_MERGE_DATA_H
#include "Data.h"
#include <unordered_map>
class merge_Data :public Data{
public:
    int times=0;//�ϲ�����
    int N;//TopN��N
    std::vector<std::pair<std::string,int>>top[200];
    std::queue<int>unprocessed,processed;//�������У�һ����¼����ģ�һ����¼δ�����
    std::mutex mtx_read;//��ȡ��
    void mergeData_init();//��ʼ��
    void mergeData_Top100_easy();//�����С�ļ���TopN
    void mergeData_read_AND_write();//�ϲ�С�ļ�
    void mergeData_Top100_finish();//�����
};
#endif