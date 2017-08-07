
无参数
##PARA0#：无参数
##PARA1#：无参数 

###

			ll1_push();
			ll1_eat_szvt( "ATASK+" + 2 );
			if( ll1_pws->m_rc )
			{
				ta3postcmd_ch = ll1_eat_uint(); 
			
				if( ta3postcmd_ch >= 3 )
				{
					ta3postcmd_ComXSendU8ss( "ERR. too large num.\x0d\x0a" );

					goto LL_AT命令处理结束;
				}


				ll1_eat_szvt( "|" );
				if( !ll1_pws->m_rc )
				{
					ta3postcmd_ComXSendU8ss( "ERR. expect check num.\x0d\x0a" );
					
					goto LL_AT命令处理结束;
				}

				ta3postcmd_check = ll1_eat_uint(); 

				
				//all ok

				sprintf( printbuf, "OK. %f,%f,%f,%f\r\n",   MPU9250_data[ta3postcmd_ch][0],
															MPU9250_data[ta3postcmd_ch][1],
															MPU9250_data[ta3postcmd_ch][2],
															MPU9250_data[ta3postcmd_ch][3]	);
				ta3postcmd_ComXSendU8ss( printbuf );
				 
				
			
				goto LL_AT命令处理结束;
				
			}
			else
			{
				ll1_pop();
			}



