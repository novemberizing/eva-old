__DESCRIPTOR HANDLE APPLICATION PROGRAMMING INTERFACE__
=======================================================

사용자가 알아야 할 필요는 없다.

디스크립터 핸들은 OS 마다 상이하게 구현이 필요한 경우를 위하여 유니온 타입으로 구현되어 있습니다. POSIX 의 경우 입출력을 위한 디스크립터는 32비트 정수형을 사용하지만, 윈도우즈는 핸들 타입을 사용하기 때문에, 멀티 플랫폼을 지원할 경우의 일관적인 접근법을 위하여 유니온 타입으로 정의하였습니다.

TODO: ClassDiagramDescriptorHandle.jpg

