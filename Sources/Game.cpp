#include "Game.hpp"


// TODO: 砲台の位置を画面左に、ターゲットの位置を画面右に移動させる。(A) hw16a057北尾勇人
// TODO: 雲の位置を左から右に動かす。見えなくなったら左端に戻す。(B) hw16a057北尾勇人
// TODO: 砲台を青い壁に沿って上下に動かす。(C) hw16a057北尾勇人
// TODO: 弾のスピードを速くし、弾が画面右端を通り越したら再度発射可能にする。(D)
// TODO: スコアのサイズを大きくする。(E)
// TODO: スコアを100点ずつ加算するようにし、5桁の表示に変える。(F)
// TODO: PlayBGM()関数を使って、BGMを再生する。(G)
// TODO: PlaySE()関数を使って、弾の発射時とターゲットに当たった時にSEを再生する。(H)

Vector2 cloudPos;       //!< 雲の位置
Vector2 cannonPos;      //!< 砲台の位置
Vector2 bulletPos;      //!< 弾の位置
Rect    targetRect;     //!< ターゲットの矩形
int     score;          //!< スコア
int changePos;          //!<移動


// ゲーム開始時に呼ばれる関数です。
void Start()
{
    cloudPos = Vector2(-320, 100);
    cannonPos = Vector2(-310, -150);
    targetRect = Rect(280, -140, 40, 40);
    bulletPos.x = -999;
    score = 0;
    
    PlayBGM("bgm_maoudamashii_8bit07.mp3");
}

// 1/60秒ごとに呼ばれる関数です。モデルの更新と画面の描画を行います。
void Update()
{
    // 弾の発射
    if (bulletPos.x <= -999 && Input::GetKeyDown(KeyMask::Space)) {
        bulletPos = cannonPos + Vector2(50, 10);
        PlaySound("se_maoudamashii_explosion03.mp3");
    }
    
    // 弾の移動
    if (bulletPos.x > -999) {
        bulletPos.x += 10 * Time::deltaTime;
        bulletPos.x += 200 * Time::deltaTime;
         if (bulletPos.x > 310){
             bulletPos.x =-999;
         }
        
        // ターゲットと弾の当たり判定
        Rect bulletRect(bulletPos, Vector2(32, 20));
        if (targetRect.Overlaps(bulletRect)) {
            score += 100;         // スコアの加算
            bulletPos.x = -999; // 弾を発射可能な状態に戻す
            PlaySound("se_maoudamashii_explosion06.mp3");
        }
    }
    
    // 背景の描画
    Clear(Color::cyan);
    FillRect(Rect(-320, -240, 640, 100), Color::green);
    cloudPos.x += 3;
    if(cloudPos.x > 300){
        cloudPos.x = -600;
    }

    // 雲の描画
    DrawImage("cloud1.png", cloudPos);
    
    // 弾の描画
    if (bulletPos.x > -999) {
        DrawImage("bullet.png", bulletPos);
    }
    
    // 砲台の描画
    FillRect(Rect(cannonPos.x-10, -140, 20, 100), Color::blue);
    DrawImage("cannon.png", cannonPos);
    if(cannonPos.y >= -70) {
        changePos = -1;
    }
    if (cannonPos.y <= -150) {
        changePos = 1;
    }
    cannonPos.y += 1*changePos;
 
    // ターゲットの描画
    FillRect(targetRect, Color::red);
    
    // スコアの描画
    SetFont("nicoca_v1.ttf", 50.0f);
    DrawText(FormatString("%05d", score), Vector2(-319, 199), Color::black);
    DrawText(FormatString("%05d", score), Vector2(-320, 200), Color::white);
}

