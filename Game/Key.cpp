//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   Key.cpp
//!
//! @brief  キーボード関連の処理
//!
//! @date   2018/08/08
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
	int i;
	for (i = 0; i<256; i++) {
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
	int later = 0;

	//各キーの入力状態
	int key_state1, key_state2;

	key_state1 = CheckStateKey(Handle1);
	key_state2 = CheckStateKey(Handle2);


	if (key_state1 > 0) {	//一番目が押されていたら
		if (key_state2 > 0 && key_state2 < key_state1) {		//二番目が後に押されていたら
			later = 2;
		}
		else {
			later = 1;
		}
	}
	else if (key_state2 > 0) {	//二番目が押されていたら
		later = 2;
	}

	return later;
}

//----------------------------------------------------------------------
//! @brief ４つの特定のキーの後から押されているほうを判別する
//!
//! @param[in]	Handle1 特定のキー1のマクロ
//!				Handle2 特定のキー2のマクロ
//!				Handle3 特定のキー3のマクロ
//!				Handle3 特定のキー4のマクロ
//!
//! @return　longer 0:いずれも押されていない 1:第１引数 2:第２引数 3:第３引数 4:第４引数
//----------------------------------------------------------------------
int CheckStateKeyLater4(unsigned char Handle1, unsigned char Handle2, unsigned char Handle3, unsigned char Handle4) {

	//デフォルトは何も押されていない状態
	int later = 0;

	//ボタンが押された時間
	int shortest = 999999;

	//各キーの入力状態
	int key_state[4];

	key_state[0] = CheckStateKey(Handle1);
	key_state[1] = CheckStateKey(Handle2);
	key_state[2] = CheckStateKey(Handle3);
	key_state[3] = CheckStateKey(Handle4);

	int i;
	for (i = 0; i < 4; i++) {
		if (key_state[i] && key_state[i] < shortest) {
			later = i + 1;
			shortest = key_state[i];
		}
	}
	
	return later;
}