// dllmain.cpp : DLL �A�v���P�[�V�����̃G���g�� �|�C���g���`���܂��B

#include "stdafx.h"

static JavaVM* jvm_1(NULL);
HINSTANCE jvmDllModule(NULL);

HANDLE gHModule;
CRITICAL_SECTION gSection;

#ifndef tstring
typedef std::basic_string<_TCHAR> tstring;
#endif

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		InitializeCriticalSection(&gSection);
		gHModule = hModule;
		break;
	case DLL_PROCESS_DETACH:
		DeleteCriticalSection(&gSection);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	}
	return TRUE;
}

void CreateSingleJavaVM()
{
	if (jvm_1 != NULL) {
		return;
	}
	//DLL���W���[���̂���t�H���_�̃p�X��p��
	_TCHAR dllDirTmp[_MAX_PATH] = _T("");
	GetModuleFileName((HMODULE) gHModule, dllDirTmp, _MAX_PATH);
	tstring dllDir(dllDirTmp);
	dllDir.replace(dllDir.find(_T("\\JavaManager.dll")), 16, _T(""));

	//Jvm.dll�����[�h����
	//�i�ȉ��͐�΃p�X�̗Ⴞ�����ۂ�JRE��dllDir����̑��΃p�X�ɔz�u���đ��΃p�X�ɂ���Ɨǂ��j
	//�i���邢�̓��W�X�g������jvm.dll�̃p�X��T���Ă��ǂ��j
	tstring jvmDll = _T("C:\\PROGRA~1\\Java\\jdk1.7.0_21\\jre\\bin\\server\\jvm.dll");
	jvmDllModule = LoadLibrary(jvmDll.c_str());
	if (jvmDllModule == NULL) {
		throw jni_util::JVM_LOAD_ERROR;
	}

	//JNI_CreateJavaVM�֐��̗p��
	int (__stdcall * createJavaVM)(JavaVM **, void **, void *);
	createJavaVM = (int (__stdcall *)(JavaVM **, void **, void *))
				   GetProcAddress(jvmDllModule, "JNI_CreateJavaVM");
	
	//jar��u��lib�t�H���_��DLL���W���[���̂���t�H���_����̑��΃p�X�Ŏw�肷��	
	tstring libDir(dllDir);
	libDir += _T("\\lib\\");
	tstring searchPath(dllDir);
	searchPath += _T("\\lib\\*.jar");

	//lib�t�H���_����jar���������A�N���X�p�X������ɒǉ�����
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile(searchPath.c_str(), &fd);	

	tstring classpathStr = _T("-Djava.class.path=.;");
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			classpathStr += libDir;
			classpathStr += fd.cFileName;
			classpathStr += _T(";");
		} while (FindNextFile(hFind, &fd));
	}
	FindClose(hFind);

	//�N���X�p�X�������char�ɕϊ�
#ifdef UNICODE
	size_t len;
	wcstombs_s(&len, NULL, NULL, classpathStr.c_str(), NULL);
	char* classpathOptStr = new char[len];
	wcstombs_s(&len, classpathOptStr, len, classpathStr.c_str(), len);
#else
	const char* classpathOptStr = classpathStr.c_str();
#endif

	//JVM�𐶐�
	JavaVMInitArgs vm_args;
	std::vector<JavaVMOption> opts;
	JavaVMOption clsPathOpt;
	clsPathOpt.optionString = classpathOptStr;
	opts.push_back(clsPathOpt);

	JavaVMOption* options = new JavaVMOption[opts.size()];
	for (size_t i = 0, l = opts.size(); i < l; i++) {
		options[i] = opts.at(i);
	}
	vm_args.options = options;
	vm_args.nOptions = (jint)opts.size();
	vm_args.version = JNI_VERSION_1_6;
	vm_args.ignoreUnrecognized = JNI_TRUE;

	JNIEnv* env = NULL;
	int status;
	try {
		status = createJavaVM(&jvm_1, (void**)&env, &vm_args);
	} catch (...) {
		throw jni_util::CREATE_JVM_ERROR;
	}
	
	delete [] options;
	options = NULL;
	
#ifdef UNICODE
	delete [] classpathOptStr;
	classpathOptStr = NULL;
#endif

	switch (status) {
	case JNI_OK:
		break;
	case JNI_ERR:
		throw jni_util::CREATE_JVM_ERROR;
	case JNI_ENOMEM:
		throw jni_util::NOMEM_ERROR;
	}
}

void jni_util::GetRightJNIEnv(void **penv)
{
	if (jvm_1 == NULL) {
		EnterCriticalSection(&gSection);
		CreateSingleJavaVM();
		LeaveCriticalSection(&gSection);
	}

	jint ret = jvm_1->GetEnv(penv, JNI_VERSION_1_6);
	if (ret != JNI_OK) {
		ret = jvm_1->AttachCurrentThread(penv, NULL);
		if (ret != JNI_OK) {
			throw jni_util::GET_JNIENV_ERROR;
		}
	}
}

void jni_util::ReleaseJNIEnv()
{
	jvm_1->DetachCurrentThread();
}


