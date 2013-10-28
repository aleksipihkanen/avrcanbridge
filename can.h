/* Very crude initialization to normal mode 125kbps */
void can_init(void)
{
	uint8_t i;
	CANGCON = (1 << SWRES);
	CANGIT = 0;
	for (i = 0; i < 15; i++) {
		CANPAGE = i << 4;
		CANCDMOB = 0;
		CANSTMOB = 0;
	}
	CANBT1 = 0x0e;
	CANBT2 = 0x0c;
	CANBT3 = 0x37;
	CANTCON = 0x00;
	CANGCON = 0x02;
}

void can_send(uint16_t id, uint8_t * data, uint8_t len)
{
	uint8_t i;
	CANPAGE = 0;
	CANIDT4 = 0x00;
	CANIDT3 = 0x00;
	CANIDT2 = id << 5;
	CANIDT1 = id >> 3;
	for (i = 0; i < len; i++)
		CANMSG = data[i];
	CANCDMOB = 0x40 | len;	// enable transmission
	CANSTMOB = 0x00;
}
