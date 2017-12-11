#include "kernel.h"
#include "kernel_id.h"
#include "MinSys3069.h"
#include "sample.h"


/* スタートアップルーチンから最初に呼び出される初期化関数 */
/* OS起動前にすること（SCIの初期化など）を行っておく      */
/* この関数からスタートアップルーチンに戻った後に，       */
/* スタートアップルーチンはHOSを呼び出す                  */
void preStartHos()
{
	initSCI1();              /* SCIの初期化 */
	SCI1_printf("\npreStartHos: start!\n");  /* 開始メッセージ */
}

ID	tskIDA, tskIDB ;

/* HOS下で最初に起動するハンドラ*/
/* system.cfg中で静的に起動される */
void OnHosStart(VP_INT exinf)
{
	const static T_CTSK pk_ctskA = { TA_HLNG, 1, taskA, 6, 256, NULL};
	const static T_CTSK pk_ctskB = { TA_HLNG, 1, taskB, 5, 256, NULL};
	ER_ID	tskid ;

	putStringSCI1("OnHosStart: starting!\n");

	if( ( tskid = acre_tsk( &pk_ctskA ) ) <= E_OK ) {
		SCI1_printf( "acre_tsk error %d\n", tskid ) ;
	} else {
		tskIDA= tskid ;
	}

	if( ( tskid = acre_tsk( &pk_ctskB ) ) <= E_OK ) {
		SCI1_printf( "acre_tsk error %d\n", tskid ) ;
	} else {
		tskIDB= tskid ;
	}
	act_tsk( tskIDA );
}

/* #define USE_SEMAPHO */

#ifdef USE_SEMAPHO	/* semaphoを利用する場合 */

void taskA(VP_INT exinf)
{
	int i ;

	putStringSCI1( "taskA: starting!\n" ) ;
	dly_tsk( 2 ) ;
	act_tsk( tskIDB ) ;

	for( i = 0 ; i < 3 ; i++ ) {
		wai_sem(SEMID_SCI); /* semapho資源の獲得 */
		putStringSCI1( "Department of Computer Science, Tokyo National College of Technology.\n" ) ;
		sig_sem(SEMID_SCI); /* semapho資源の返却 */
	}
	ext_tsk( ) ;
}

void taskB(VP_INT exinf)
{
	int i ;
	putStringSCI1( "taskB: starting!\n" ) ;
	dly_tsk( 2 ) ;

	for( i = 0 ; i < 10 ; i++ ) {
		wai_sem(SEMID_SCI); /* semapho資源の獲得 */
		putStringSCI1( "[TNCT]\n" ) ;
		sig_sem(SEMID_SCI); /* semapho資源の返却 */
		dly_tsk( 2 ) ;
	}
	ext_tsk( ) ;
}

#else
/*semaphoを使用しない場合*/

void taskA(VP_INT exinf)
{
	int i ;

	putStringSCI1( "taskA: starting!\n" ) ;
	dly_tsk( 2 ) ;
	act_tsk( tskIDB ) ;

	for( i = 0 ; i < 3 ; i++ ) {
		putStringSCI1( "Department of Computer Science, Tokyo National College of Technology.\n" ) ;
	}
	ext_tsk( ) ;
}

void taskB(VP_INT exinf)
{

	int i ;
	putStringSCI1( "taskB: starting!\n" ) ;
	dly_tsk( 2 ) ;

	for( i = 0 ; i < 10 ; i++ ) {
		putStringSCI1( "[TNCT]\n" ) ;
		dly_tsk( 2 ) ;
	}
	ext_tsk( ) ;
}

#endif

