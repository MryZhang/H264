// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// x264.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"
#include <assert.h>

void verify_thread_fun(DWORD& tid){
    if(tid == 0xffffffff){ 
        tid = GetCurrentThreadId();  
    }else{   
        assert(tid == GetCurrentThreadId());
    }
}