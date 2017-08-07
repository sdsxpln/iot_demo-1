
无参数
##PARA0#：无参数
##PARA1#：无参数 

###

			ll1_push();
			ll1_eat_szvt( "ATPRS+" + 2 );
			if( ll1_pws->m_rc )
			{
				ta3postcmd_ch = ll1_eat_uint(); 
			

				ll1_eat_szvt( "|" );
				if( !ll1_pws->m_rc )
				{
					ta3postcmd_ComXSendU8ss( "ERR. expect check num.\x0d\x0a" );
					
					goto LL_AT命令处理结束;
				}

				ta3postcmd_check = ll1_eat_uint(); 

				
				//all ok

				sprintf( printbuf, "OK. %ld,%ld\r\n",   g_bmp085_pressure, g_bmp085_temperature	);
				//sprintf( printbuf, "OK. %f,%f\r\n",   BMP280_Pressure, BMP280_Temperature	);
				ta3postcmd_ComXSendU8ss( printbuf );
				 
				
			
				goto LL_AT命令处理结束;
				
			}
			else
			{
				ll1_pop();
			}



