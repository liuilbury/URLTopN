#ifndef URLTOPN_SPILT_DATA_H
#define URLTOPN_SPILT_DATA_H

#include "Data.h"

//spilt_Data��Ŀ���ǲ�ִ��ļ��������˵��̶߳����߳�д�Ĳ���
class spilt_Data : public Data {
public:
    std::condition_variable repo_not_full;//���в�����������
    std::condition_variable repo_not_empty;//���в�����������
    std::mutex mtx;//��д�����Ļ�����
    std::mutex mtx_read_queue;//д������ȡ���еĻ�����
    std::mutex mtx_write_vector;//д����д��vector�Ļ�����
    std::mutex mtx_write_file;//д����д���ļ��Ļ�����
    std::queue<std::string> q;//���̷߳������ݣ�д�̶߳�ȡ���ݵĶ���
    int hash_url_cnt[200];//ĳһ��hashֵ��URL�Ѿ������������
    std::string spilt[200];//����ĳһ��hashֵ��url
    bool spilt_end = false;//�Ƿ��Ѿ���ȡ��ȫ����URL
    void spiltData_init();//��ʼ��hash_url_cnt��spilt
    void spiltData_read();//������
    void spiltData_write();//д����
    void spiltData_end();//���spiltʣ�����ȫ��д���ļ�
};

#endif