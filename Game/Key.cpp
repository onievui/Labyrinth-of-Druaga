//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Key.cpp
//!
//! @brief  キーボード関連の処理
//!
//! @date   2018/06/07
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// グローバル変数の定義 ====================================================

//キーボードの入力状態を格納する
static unsigned int g_stateKey[256];

static int g_stateKeyUp[256];

// 関数の定義 ==============================================================
//----------------------------------------------------------------------
//! @brief キーボードのすべてのキーの押下状態、入力フレーム数を取得する
//!
//! @param[in] なし
//!
//! @return　0:正常終了 1:異常終了
//----------------------------------------------------------------------
int GetHitKeyStateAll_2() {
	char GetHitKeyStateAll_Key[256];
	GetHitKeyStateAll(GetHitKeyStateAll_Key);
	for (int i = 0; i<256; i++) {
		if (GetHitKeyStateAll_Key[i] == 1) {
			g_stateKey[i]++;
			g_stateKeyUp[i] = 0;
		}
		else {
			if (g_stateKey[i] > 0)
				g_stateKeyUp[i] = 1;
			else
				g_stateKeyUp[i] = 0;

			g_stateKey[i] = 0;
		}
	}
	return 0;
}

//----------------------------------------------------------------------
//! @brief 特定のキーの入力状態を返す
//!
//! @param[in]	Handle 特定のキーのマクロ
//!
//! @return　g_statekey[Handle] 特定のキーの入力フレーム数
//----------------------------------------------------------------------
int CheckStateKey(unsigned char Handle) {
	return g_stateKey[Handle];
}


//----------------------------------------------------------------------
//! @brief 特定のキーを押していない状態から押したかどうかを返す
//!
//! @param[in]	Handle 特定のキーのマクロ
//!
//! @return　0:押していない 1:押した
//----------------------------------------------------------------------
int CheckHitKeyDown(unsigned char Handle) {
	return g_stateKey[Handle] == 1 ? 1 : 0;
}


//----------------------------------------------------------------------
//! @brief 特定のキーを押した状態から離したかどうかを返す
//!
//! @param[in]	Handle 特定のキーのマクロ
//!
//! @return　0:離していない 1:離した
//----------------------------------------------------------------------
int CheckHitKeyUp(unsigned char Handle) {
	return g_stateKeyUp[Handle];
}


//----------------------------------------------------------------------
//! @brief ２つの特定のキーの後から押されているほうを判別する
//!
//! @param[in]	Handle1 特定のキー1のマクロ
//!				Handle2 特定のキー2のマクロ
//!
//! @return　longer 0:どちらも押されていない 1:第１引数 2:第２引数
//----------------------------------------------------------------------
int CheckStateKeyLater(unsigned char Handle1, unsigned char Handle2) {

	//デフォルトは何も押されていない状態
	int longer = 0;

	if (CheckStateKey(Handle1) > 0) {	//左が押されていたら
		if (CheckStateKey(Handle2) > 0 && CheckStateKey(Handle2) < CheckStateKey(Handle1)) {		//右が後に押されていたら
			longer = 2;
		}
		else {
			longer = 1;
		}
	}
	else if (CheckStateKey(Handle2) > 0) {	//右が押されていたら
		longer = 2;
	}

	return longer;
}