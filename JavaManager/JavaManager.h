#pragma once

#ifdef JAVAMANAGER_EXPORTS
#define JAVAMANAGER_API __declspec(dllexport)
#else
#define JAVAMANAGER_API __declspec(dllimport)
#endif

namespace jni_util
{
	/**
	 * �X���b�h��Ăяo���񐔂Ɋւ炸��ɐ�����JNIEnv��Ԃ��B
	 */
	JAVAMANAGER_API void GetRightJNIEnv(void **penv);
	
	/**
	 * ���݂̃X���b�h��JNIEnv���g���I��������ɌĂԁB
	 */
	JAVAMANAGER_API void ReleaseJNIEnv();
}