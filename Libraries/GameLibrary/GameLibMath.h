////__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
////! @file   GameLibMath.h
////!
////! @brief  DxLibの数学関連への追加機能のヘッダファイル
////!
////! @date   2018/7/1
////!
////! @author ********
////__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//
//// 多重インクルードの防止 ==================================================
//#pragma once
//
//
//
//
//// ヘッダファイルの読み込み ================================================
//#include <minwindef.h>
//
//
//
//
//// 型の定義 ================================================================
//
//// <2Dのベクトル> ------------------------------------------------------
//struct tag_Vector2D
//{
//	float x;    // X成分
//	float y;    // Y成分
//};
//typedef struct tag_Vector2D Vector2D;
//
//
//// <2Dのサイズ> --------------------------------------------------------
//struct tag_Size2D
//{
//	float width;     // 幅
//	float height;    // 高さ
//};
//typedef struct tag_Size2D Size2D;
//
//
//// <2Dの矩形> ----------------------------------------------------------
//struct tag_Rect2D
//{
//	float x;         // 左上頂点のX座標
//	float y;         // 左上頂点のY座標
//	float width;     // 幅
//	float height;    // 高さ
//};
//typedef struct tag_Rect2D Rect2D;
//
//
//// <2Dの範囲> ----------------------------------------------------------
//struct tag_Bounds2D
//{
//	float left;      // 左端
//	float top;       // 上端
//	float right;     // 右端
//	float bottom;    // 下端
//};
//typedef struct tag_Bounds2D Bounds2D;
//
//
//// <基本形状> ----------------------------------------------------------
//// 2Dの点
//typedef Vector2D Point2D;
//
//
//// 2Dの直線
//struct tag_Line2D
//{
//	Point2D  p;    // 直線の通る点
//	Vector2D v;    // 方向ベクトル
//};
//typedef struct tag_Line2D Line2D;
//
//
//// 2Dの線分
//struct tag_Segment2D
//{
//	Point2D  start;    // 始点
//	Point2D  end;      // 終点
//};
//typedef struct tag_Segment2D Segment2D;
//
//
//// 2Dの円
//struct tag_Circle2D
//{
//	Point2D center;    // 中心座標
//	float   radius;    // 半径
//};
//typedef struct tag_Circle2D Circle2D;
//
//
//// 2Dの三角形
//struct tag_Triangle2D
//{
//	Point2D vertices[3];    // 頂点
//};
//typedef struct tag_Triangle2D Triangle2D;
//
//
//// 2Dの箱形
//struct tag_Box2D
//{
//	Point2D center;    // 中心座標
//	Size2D  size;      // サイズ
//};
//typedef struct tag_Box2D Box2D;
//
//
//// 2Dのカプセル
//struct tag_Capsule2D
//{
//	Segment2D segment;    // 線分
//	float     radius;     // 半径
//};
//typedef struct tag_Capsule2D Capsule2D;
//
//
//
//
//// 関数の宣言 ==============================================================
//
//// <角度の単位変換> ----------------------------------------------------
//
//// [度]から[ラジアン]への単位変換
//float ToRadians(float degree);
//
//// [ラジアン]から[度]への単位変換
//float ToDegrees(float radian);
//
//
//
//// <数値> --------------------------------------------------------------
//
//// 指定した値を下限～上限の範囲内に収める
//int   ClampI(int   x, int   min, int   max);
//float ClampF(float x, float min, float max);
//
//// 浮動小数点数型の誤差を考慮に入れた比較
//BOOL FloatEquals(float a, float b);
//
//
//
//// <生成> --------------------------------------------------------------
//// 2Dのベクトルの生成
//Vector2D CreateVector2D(float x, float y);
//
//// 2Dのサイズの生成
//Size2D CreateSize2D(float width, float height);
//
//// 2Dの矩形の生成
//Rect2D CreateRect2D(float x, float y, float width, float height);
//
//// 2Dの範囲の生成
//Bounds2D CreateBounds2D(float left, float top, float right, float bottom);
//
//// 2Dの点の生成
//Point2D CreatePoint2D(float x, float y);
//
//// 2Dの直線の生成
//Line2D CreateLine2D(Point2D p, Vector2D v);
//Line2D CreateLine2D(float px, float py, float vx, float vy);
//
//// 2Dの線分の生成
//Segment2D CreateSegment2D(Point2D start, Point2D end);
//Segment2D CreateSegment2D(float sx, float sy, float ex, float ey);
//
//// 2Dの円の生成
//Circle2D CreateCircle2D(Point2D center, float radius);
//Circle2D CreateCircle2D(float cx, float cy, float radius);
//
//// 2Dの三角形の生成
//Triangle2D CreateTriangle2D(Point2D p1, Point2D p2, Point2D p3);
//Triangle2D CreateTriangle2D(float x1, float y1, float x2, float y2, float x3, float y3);
//
//// 2Dの箱形の生成
//Box2D CreateBox2D(Point2D center, Size2D size);
//Box2D CreateBox2D(float cx, float cy, float width, float height);
//
//// 2Dのカプセルの生成
//Capsule2D CreateCapsule2D(Segment2D segment, float radius);
//Capsule2D CreateCapsule2D(Point2D p1, Point2D p2, float radius);
//Capsule2D CreateCapsule2D(float x1, float y1, float x2, float y2, float radius);
