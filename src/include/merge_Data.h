#ifndef URLTOPN_MERGE_DATA_H
#define URLTOPN_MERGE_DATA_H
#include "Data.h"
#include <unordered_map>
class merge_Data :public Data{
public:
    int times=0;
    int N;
    std::vector<std::pair<std::string,int>>top[200];
    std::queue<int>unprocessed,processed;//�������У�һ����¼����ģ�һ����¼δ�����
    std::mutex mtx_read;//��ȡ��
    void mergeData_init();
    void mergeData_Top100_easy();
    void mergeData_read_AND_write();
    void mergeData_Top100_finish();
};
#endif