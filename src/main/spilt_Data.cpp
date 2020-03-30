#include "spilt_Data.h"

void spilt_Data::spiltData_init() {//��ʼ��
    for (int i = 0; i < 200; i++) {
        hash_url_cnt[i] = 0;
        spilt[i] = "";
    }
}

void spilt_Data::spiltData_read() {
    std::ifstream in(filename);//���ļ�
    std::string query;
    while (true) {
        if (getline(in, query)) {//��ȡһ��
            std::unique_lock<std::mutex> lock(mtx);//��Ҫ��������ʱ����
            if (q.size() == looptimes / 200 / 200) {
                repo_not_full.wait(lock);//������ʱ�ͷ�����������ʱ�����
            }
            q.push(query);
            repo_not_empty.notify_one();//������������������߳�
            lock.unlock();//����
        } else {
            spilt_end = true;
            return;
        }
    }
}

void spilt_Data::spiltData_write() {
    while (true) {
        std::unique_lock<std::mutex> lock_read_queue(mtx_read_queue);//д�߳���
        std::unique_lock<std::mutex> lock(mtx);//��Ҫ��ȡ����ʱ����
        if (q.empty()) {
            if (spilt_end) {//���������ʶΪtrue�Ҷ���Ϊ�գ����˳�
                lock_read_queue.unlock();
                lock.unlock();
                break;
            }
            repo_not_empty.wait(lock);//���п�ʱ�ͷ�����������ʱ�����
        }
        std::string query = q.front();
        q.pop();
        repo_not_full.notify_one(); //������������������߳�
        lock.unlock();
        lock_read_queue.unlock();
        std::hash<std::string> ss;
        int ha_sh = ss(query) % 200;
        std::unique_lock<std::mutex> lock_write_vector(mtx_write_vector);//д�߳���ʹ��vector��ʱ�򲻱�����
        spilt[ha_sh] = spilt[ha_sh] + query + "\n";//�ַ���ƴ��
        hash_url_cnt[ha_sh]++;
        if (hash_url_cnt[ha_sh] != looptimes / 200 / 200) {//��hash_url_cnt[ha_sh]�������Ϊlooptimes/200/200ʱ������д����
            lock_write_vector.unlock();
        } else {
            std::string outstring = spilt[ha_sh];
            spilt[ha_sh] = "";
            hash_url_cnt[ha_sh] = 0;
            lock_write_vector.unlock();
            std::unique_lock<std::mutex> lock_write_file(mtx_write_file);//д�߳���ʹ���ļ���ʱ�򲻱�����
            std::ofstream out("../../../data/spiltData/" + std::to_string(ha_sh) + ".txt", std::ios::app);
            out << outstring;
            out.close();
            lock_write_file.unlock();
        }
    }
}

void spilt_Data::spiltData_end() {//д�߳�ȫ���˳���spilt�ﻹ��ʣ��URL��Ҫ����
    for (int i = 0; i < 200; i++) {
        if (spilt[i].size() == 0)
            continue;
        std::ofstream out("../../../data/spiltData/" + std::to_string(i) + ".txt", std::ios::app);
        out << spilt[i];
        spilt[i] = "";
        out.close();
    }
}