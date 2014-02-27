// JNI_SAMPLE.cpp : �R���\�[�� �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B

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
			std::wcout << _T("JVM.dll�����[�h�ł��܂���B") << std::endl;
			std::wcout << _T("JVM.dll�̃p�X�̏C�����K�v�ł��B") << std::endl;
			std::wcout << _T("x64�ł̎��s�ɂ�x64�ł�JVM.dll�̃p�X���Ax86�ł̎��s�ɂ�x86�ł�JVM.dll�̃p�X���K�v�ł��B") << std::endl;
		}
		return e;
	}

	//Date�N���X��p��
	jclass dateCls = env->FindClass("Ljava/util/Date;");
	assert(dateCls != NULL);

	//Date�N���X�̃R���X�g���N�^��toString,after���\�b�h��p��
	jmethodID mid_constractor = env->GetMethodID(dateCls, "<init>", "()V");
	jmethodID mid_toString = env->GetMethodID(dateCls, "toString", "()Ljava/lang/String;");
	jmethodID mid_after = env->GetMethodID(dateCls, "after", "(Ljava/util/Date;)Z");
	assert(mid_constractor != NULL &&
		   mid_toString != NULL &&
		   mid_after != NULL);

	//Date�N���X�̃I�u�W�F�N�g�𐶐�
	jobject obj = env->NewObject(dateCls, mid_constractor);

	//�Ƃ肠����toString���Ă�ŏo�͂��Ă݂�ijchar�����̂܂�wchar_t�Ƃ��Ďg�����j�B
	jstring dateStr = (jstring) env->CallObjectMethod(obj, mid_toString);
	const jchar* tmp = env->GetStringChars(dateStr, false);
	std::wcout << (wchar_t*)tmp << std::endl;

	//after���\�b�h��null��n����NullPointerException�𔭐�������B
	jboolean b = env->CallBooleanMethod(obj, mid_after, NULL);
	if (env->ExceptionCheck()) {
		//�G���[���o��
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