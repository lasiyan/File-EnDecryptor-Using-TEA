# File-EnDecryptor-Using-TEA

File Encryption and Decryption application using Tiny Encryption Algorithm. This program made by C++ and Microsoft Foundation Class in Visual Studio 2015 community version

File EnDecryptor은 작지만 강력한 알고리즘인 TEA를 사용한 쉽고 빠른 암호화 및 복호화 프로그램입니다. 7개의 숫자 키 값을 통해 파일을 암호화하여 타인으로 하여금 파일의 내용을 보호하고, 해당 키 값을 통해 다시 복호화하여 열어볼 수 있습니다.

## 개발 환경

* OS : Windows 10 Pro 64bit
* CPU : Intel(R) Core(TM) i5-5200U CPU @ 2.20GHz 2.20 GHz
* RAM : 4.00GB
* IDE : Microsoft Visual Studio Community 2015

## 사용 기술

C(Make DLL), C++, Window API, MFC, Tiny Encryption Algorithm

## 부가 설명

 해당 어플리케이션은 작지만 강력한 알고리즘 TEA를 사용하여 암호화 및 복호화를 진행합니다. MFC Dialog Box를 사용하여 구현된 해당 프로그램은 먼저 프로그램의 핵심 로직인 TEA 알고리즘을 사용한 FileEecoding 및 FileDecoding 함수를 생성하고, 해당 함수 안에서 TEA 로직을 수행한 후 암호화 과정에서 사용자가 입력한 키 값을 파일의 후미에 저장시킵니다. 마찬가지로 복호화 과정 역시 해당 함수에서 사용자가 입력한 키 값을 토대로 먼저 복호화가 가능한지 여부를 판단 후, 암호화 키 값과 동일하면 해당 파일을 복호화하고 만약 동일하지 않은 키 값이 입력될 경우 false를 반환합니다. 

 이러한 함수는 모두 C 기반으로 프로그래밍 되어 있고, 해당 로직(함수)들을 MCF 기반 프로그램에서 사용하기 위해 DLL을 사용합니다. FileEncoding과 FileDecoding 함수는 extern "C" __declspec(dllexport) 형식으로 선언되어 있고, 이는 MFC DLL 형식의 DLLCreator 프로젝트에 의하여 동적 링크 라이브러리로 생성됩니다. 그리고 프로그램의 프레임을 구현한 FileEnDecryptor 프로젝트에서 해당 DLL을 링크시키고 참조하여 Encrypt 와 Decrypt 버튼 로직을 수행합니다.

## 실행 방법

* 해당 프로그램을 실행하기 위해서는 MFC Library가 필요합니다. Visual Studio 기준 설치 시 옵션을 토대로 제공됩니다.
* FileEnDecryptor.sln 솔루션을 실행합니다.
* DLLCreator 프로젝트를 선택하고 마우스 우클릭 하여 해당 프로젝트를 빌드시킵니다.
* 다음으로 FileEnDecryptor 프로젝트를 마우스 우클릭하여 해당 프로젝트를 빌드시킵니다.
* 솔루션이 위치한 경로에 x64 폴더가 생성되고 그 안 release 폴더 안에 FileEnDecryptor.exe 파일이 생성됩니다.
* 해당 exe 파일은 반드시 dll과 동일한 경로에 위치하여야 합니다.

## 실행 결과

[![Demo Doccou alpha](https://j.gifs.com/LgrOX4.gif)](https://www.youtube.com/watch?v=T0kKgBKwio0)

(클릭 시 유튜브로 이동합니다)
