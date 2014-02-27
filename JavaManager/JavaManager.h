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
	 * スレッドや呼び出し回数に関らず常に正しいJNIEnvを返す。
	 */
	JAVAMANAGER_API void GetRightJNIEnv(void **penv);
	
	/**
	 * 現在のスレッドでJNIEnvを使い終わった時に呼ぶ。
	 */
	JAVAMANAGER_API void ReleaseJNIEnv();
}