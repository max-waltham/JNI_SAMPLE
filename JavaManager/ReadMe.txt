========================================================================
 ダイナミック リンク ライブラリ: JavaManager プロジェクトの概要
========================================================================

この JavaManager DLL は、AppWizard により作成されました。

このファイルには、JavaManager 
アプリケーションを構成する各ファイルの内容の概要が含まれています。


JavaManager.vcxproj
    これは、アプリケーション ウィザードを使用して生成された VC++ 
    プロジェクトのメイン プロジェクト ファイルです。
    ファイルを生成した Visual C++ のバージョンに関する情報と、アプリケーション 
    ウィザードで選択されたプラットフォーム、
    構成、およびプロジェクト機能に関する情報が含まれています。

JavaManager.vcxproj.filters
    これは、アプリケーション ウィザードで生成された VC++ プロジェクトのフィルター 
    ファイルです。 
    このファイルには、プロジェクト内のファイルとフィルターとの間の関連付けに関する
    情報が含まれています。 この関連付けは、特定のノー
    ドで同様の拡張子を持つファイルのグループ化を
    示すために IDE で使用されます (たとえば、".cpp" ファイルは "ソース ファイル" 
    フィルターに関連付けられています)。

JavaManager.cpp
    これは、メインの DLL ソース ファイルです。

    この DLL の作成時には、シンボルがエクスポートされません。 このため、ビルド時に 
    .lib ファイルが生成されません。
    このプロジェクトを他のプロジェクトの依存関係に追加する場合は、
    コードを追加して DLL からシンボルをエクスポートし、エクスポート 
    ライブラリが生成されるようにするか、またはプロジェクトの [プロパティ ページ] 
    ダイアログ ボックスにある [リンカー] フォルダーの[全般] プロパティ 
    ページで、"インポート ライブラリの無視" プロパティを[はい] に設定します。

/////////////////////////////////////////////////////////////////////////////
その他の標準ファイル :

StdAfx.h、StdAfx.cpp
    これらのファイルは、JavaManager.pch 
    という名前のプリコンパイル済みヘッダー (PCH) ファイルと、StdAfx.obj 
    という名前のプリコンパイル済みの型ファイルを構築するために使用されます。

/////////////////////////////////////////////////////////////////////////////
その他のメモ :

AppWizard では "TODO:" 
コメントを使用して、ユーザーが追加またはカスタマイズする必要のあるソース 
コードを示します。

/////////////////////////////////////////////////////////////////////////////
[LICENSE]

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                    Version 2, December 2004

 Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.

[/LICENSE]