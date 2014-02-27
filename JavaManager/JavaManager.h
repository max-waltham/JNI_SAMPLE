#pragma once

#ifdef JAVAMANAGER_EXPORTS
#define JAVAMANAGER_API __declspec(dllexport)
#else
#define JAVAMANAGER_API __declspec(dllimport)
#endif

namespace jni_util
{
	const int JVM_LOAD_ERROR = -1;
	const int CREATE_JVM_ERROR = -2;
	const int NOMEM_ERROR = -3;
	const int GET_JNIENV_ERROR = -4;

	/**
	 * �X���b�h��Ăяo���񐔂Ɋւ炸��ɐ�����JNIEnv��Ԃ��B
	 */
	JAVAMANAGER_API void GetRightJNIEnv(void **penv);
	
	/**
	 * ���݂̃X���b�h��JNIEnv���g���I��������ɌĂԁB
	 */
	JAVAMANAGER_API void ReleaseJNIEnv();
}