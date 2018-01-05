#include <Windows.h>
#include <sstream>
#include <locale>
#include "Window.h"
#include "DirectX11.h"
#include "Model.h"
#include "Matrix.h"
#include "MyMath.h"
#include "Time.h"

using namespace Lib;

const float FPS = 60.0f;    // 実行したいfps
const float SPEED = 0.001f; // ライトの移動速度

int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
    UNREFERENCED_PARAMETER(hInstance);
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    UNREFERENCED_PARAMETER(nCmdShow);

    // ウィンドウの作成
    auto w = std::make_shared<Lib::Window>(L"3DCGLib", 1026, 768);

    // DirectXのインスタンスの取得
    auto& directX = Lib::DirectX11::getInstance();
    directX.initDevice(w);

    // ViewMatrixの初期化
    Vector3 eye = Vector3(0.0f, 1.0f, -15.0f); // カメラの座標
    Vector3 at  = Vector3(0.0f, 1.0f,  0.0f); // 注視対象
    Vector3 up  = Vector3::UP;                // 現在のワールド座標の上方向
    auto view   = Matrix::LookAtLH(eye, at, up);
    directX.setViewMatrix(view);

    // ProjectionMatrixの初期化
    LONG windowWidth  = w->getWindowRect().right  - w->getWindowRect().left;
    LONG windowHeight = w->getWindowRect().bottom - w->getWindowRect().top;
    auto projection   = Matrix::perspectiveFovLH(MyMath::PIDIV2, windowWidth / static_cast<float>(windowHeight), 0.01f, 100.0f);
    directX.setProjectionMatrix(projection);
    
    // モデルの作成
    Model model = Model(36);
    Matrix world;
    world = Matrix::Identify;
    model.setWorldMatrix(world);

    // ライトの位置
    float posX =  0.0f;
    float posY =  0.5f;
    float posZ = -2.0f;
    model.getLightPos().translate(posX, posY, posZ);

    // 説明
    MessageBox(
        w->getHWND(),
        L"平行光源：〇、点光源：×、スポットライト：× \r\n 拡散光：×、環境光：×、反射光：◯ \r\n「W」「A」「S」「D」「E」「Q」でモデルの回転",
        L"操作説明",
        MB_OK | MB_ICONINFORMATION);

    // 更新処理
    Time time = Time();
    int fps = 0;
    float countTime = 0.0f;
    float deltaTime = 0.0f;
    std::ostringstream oss;
    WCHAR wcstr[50];
    size_t size = 0;
    setlocale(LC_ALL, "japanese"); // 後のmbstowcs_sの為の処理
    
    while (w->Update().message != WM_QUIT) {
        directX.begineFrame();

        // FPSの固定
        if (!time.timeOver(1000.0f / FPS)) {
            continue;
        }

        deltaTime = time.getDeltaTime();
        countTime += deltaTime;

        // 1秒に１回行う処理
        if (countTime > 1000.0f) {
            // fpsをデバッガに出力
            oss.str("");
            oss << "fps: " << fps << std::endl;
            mbstowcs_s(&size, wcstr, 20, oss.str().c_str(), _TRUNCATE);
            OutputDebugString(wcstr);
            // 変数のリセット
            fps = 0;
            countTime = 0.0f;
        }
        time.reset();
        ++fps;

        // 移動        
        posX = posY = posZ = 0.0f;

        if (w->getKeyDown('W')) {
            posZ = SPEED * deltaTime;
        }
        else if (w->getKeyDown('S')) {
            posZ = -SPEED * deltaTime;
        }
        if (w->getKeyDown('A')) {
            posX = -SPEED * deltaTime;
        }
        else if (w->getKeyDown('D')) {
            posX = SPEED * deltaTime;
        }
        if (w->getKeyDown('E')) {
            posY = SPEED * deltaTime;
        }
        else if (w->getKeyDown('Q')) {
            posY = -SPEED * deltaTime;
        }

        // ライトのモデルの制御
        model.getLightPos().translate(posX, posY, posZ);

        // 描画
        model.render(Lib::Color(Lib::Color::BLUE));

        directX.endFrame();
    }

    return 0;
}