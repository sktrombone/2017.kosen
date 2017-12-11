#include "kernel.h"
#include "kernel_id.h"
#include "MinSys3069.h"
#include "sample.h"


/* �X�^�[�g�A�b�v���[�`������ŏ��ɌĂяo����鏉�����֐� */
/* OS�N���O�ɂ��邱�ƁiSCI�̏������Ȃǁj���s���Ă���      */
/* ���̊֐�����X�^�[�g�A�b�v���[�`���ɖ߂�����ɁC       */
/* �X�^�[�g�A�b�v���[�`����HOS���Ăяo��                  */
void preStartHos()
{
	initSCI1();              /* SCI�̏����� */
	SCI1_printf("\npreStartHos: start!\n");  /* �J�n���b�Z�[�W */
}

ID	tskIDA, tskIDB ;

/* HOS���ōŏ��ɋN������n���h��*/
/* system.cfg���ŐÓI�ɋN������� */
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

#ifdef USE_SEMAPHO	/* semapho�𗘗p����ꍇ */

void taskA(VP_INT exinf)
{
	int i ;

	putStringSCI1( "taskA: starting!\n" ) ;
	dly_tsk( 2 ) ;
	act_tsk( tskIDB ) ;

	for( i = 0 ; i < 3 ; i++ ) {
		wai_sem(SEMID_SCI); /* semapho�����̊l�� */
		putStringSCI1( "Department of Computer Science, Tokyo National College of Technology.\n" ) ;
		sig_sem(SEMID_SCI); /* semapho�����̕ԋp */
	}
	ext_tsk( ) ;
}

void taskB(VP_INT exinf)
{
	int i ;
	putStringSCI1( "taskB: starting!\n" ) ;
	dly_tsk( 2 ) ;

	for( i = 0 ; i < 10 ; i++ ) {
		wai_sem(SEMID_SCI); /* semapho�����̊l�� */
		putStringSCI1( "[TNCT]\n" ) ;
		sig_sem(SEMID_SCI); /* semapho�����̕ԋp */
		dly_tsk( 2 ) ;
	}
	ext_tsk( ) ;
}

#else
/*semapho���g�p���Ȃ��ꍇ*/

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

