
无参数
##PARA0#：无参数
##PARA1#：无参数 

###

			//ATCHS+<ch_num,1~4>,<hight_time,700~2100>|<chk>;  ch speed
			

			ll1_push();
			ll1_eat_szvt( "ATCHA+" + 2 );
			if( ll1_pws->m_rc )
			{
				for( ta3postcmd_check = 0; ta3postcmd_check < 4; ta3postcmd_check++ )
				{
					ta3postcmd_speedall[ta3postcmd_check] = ll1_eat_uint(); 
					
					if( ta3postcmd_speedall[ta3postcmd_check] < 700 || ta3postcmd_speedall[ta3postcmd_check] > 2100 )
					{
						ta3postcmd_ComXSendU8ss( "ERR. speed num out of range.\x0d\x0a" );

						goto LL_AT命令处理结束;
					}

					if( ta3postcmd_check != 3 )
					{
						ll1_eat_szvt( "," );
						if( !ll1_pws->m_rc )
						{
							ta3postcmd_ComXSendU8ss( "ERR. expect speed num.\x0d\x0a" );
							
							goto LL_AT命令处理结束;
						}
					}

				}

				ll1_eat_szvt( "|" );
				if( !ll1_pws->m_rc )
				{
					ta3postcmd_ComXSendU8ss( "ERR. expect check num.\x0d\x0a" );
					
					goto LL_AT命令处理结束;
				}

				ta3postcmd_check = ll1_eat_uint(); 

				
				//all ok
				
				M12[0].m_hi_tta = ta3postcmd_speedall[0];
				M12[0].m_hi_ttb = ta3postcmd_speedall[1];
				M12[0].m_hi_ttc = ta3postcmd_speedall[2];
				M12[0].m_hi_ttd = ta3postcmd_speedall[3];

				sharedata_main_ready( &(M12[0]) , &(M12[1]) , &(M12[2]) , sizeof( struct M12Pwm_t ) );
			 
	
				ta3postcmd_ComXSendU8ss( "OK\x0d\x0a" );
			
				goto LL_AT命令处理结束;
				
			}
			else
			{
				ll1_pop();
			}



