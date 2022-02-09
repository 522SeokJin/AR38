#pragma once

void AppShaderLoad();

// 임의로 정한 규칙
// 파일명과 엔트리명은 같게해야한다.
// 버텍스쉐이더와 픽셀쉐이더의 구분을 위해서
// 엔트리명에 추가로 버텍스쉐이더면 "_VS"
// 픽셀쉐이더면 "_PS" 를 추가로 붙인다.
// ex) Color.fx -> float4 Color_VS(...), float4 Color_PS(...)