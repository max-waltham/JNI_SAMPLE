// JNI_SAMPLE.cpp : コンソール アプリケーションのエントリ ポイントを定義します。

#include "stdafx.h"

void CatchJavaException(JNIEnv* env);

int _tmain(int argc, _TCHAR* argv[])
{
	_tsetlocale(LC_ALL, _T(""));

	JNIEnv* env;
	try {
		jni_util::GetRightJNIEnv((void**)&env);
	} catch (int e) {
		if(e == jni_util::JVM_LOAD_ERROR){
			std::wcout << _T("JVM.dllがロードできません。") << std::endl;
			std::wcout << _T("JVM.dllのパスの修正が必要です。") << std::endl;
			std::wcout << _T("x64版の実行にはx64版のJVM.dllのパスが、x86版の実行にはx86版のJVM.dllのパスが必要です。") << std::endl;
		}
		return e;
	}

	//Dateクラスを用意
	jclass dateCls = env->FindClass("Ljava/util/Date;");
	assert(dateCls != NULL);

	//DateクラスのコンストラクタとtoString,afterメソッドを用意
	jmethodID mid_constractor = env->GetMethodID(dateCls, "<init>", "()V");
	jmethodID mid_toString = env->GetMethodID(dateCls, "toString", "()Ljava/lang/String;");
	jmethodID mid_after = env->GetMethodID(dateCls, "after", "(Ljava/util/Date;)Z");
	assert(mid_constractor != NULL &&
		   mid_toString != NULL &&
		   mid_after != NULL);

	//Dateクラスのオブジェクトを生成
	jobject obj = env->NewObject(dateCls, mid_constractor);

	//とりあえずtoStringを呼んで出力してみる（jcharをそのままwchar_tとして使った）。
	jstring dateStr = (jstring) env->CallObjectMethod(obj, mid_toString);
	const jchar* tmp = env->GetStringChars(dateStr, false);
	std::wcout << (wchar_t*)tmp << std::endl;

	//afterメソッドにnullを渡してNullPointerExceptionを発生させる。
	jboolean b = env->CallBooleanMethod(obj, mid_after, NULL);
	if (env->ExceptionCheck()) {
		//エラーを出力
		CatchJavaException(env);
	}

	env->DeleteLocalRef(obj);
	env->DeleteLocalRef(dateCls);
	jni_util::ReleaseJNIEnv();
	return 0;
}

void CatchJavaException(JNIEnv* env)
{
	jthrowable e = env->ExceptionOccurred();
	jclass throwableCls = env->FindClass("java/lang/Throwable");
	jmethodID midGetLocalizedMessage =
		env->GetMethodID(throwableCls, "getLocalizedMessage", "()Ljava/lang/String;");
	jstring jmessage = (jstring) env->CallObjectMethod(e, midGetLocalizedMessage);

	if (jmessage == NULL) {
		jmethodID mid_toString = env->GetMethodID(throwableCls, "toString", "()Ljava/lang/String;");
		jmessage = (jstring) env->CallObjectMethod(e, mid_toString);
	}

	if (jmessage != NULL) {
		const jchar* tmp = env->GetStringChars(jmessage, false);
		std::wcout << (wchar_t*)tmp << std::endl;
		env->ReleaseStringChars(jmessage, tmp);
		env->DeleteLocalRef(jmessage);
	}

	env->DeleteLocalRef(throwableCls);
	env->ExceptionClear();
}