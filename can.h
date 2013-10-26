/* Very crude initialization to normal mode 125kbps */
void can_init(void)
{
	uint8_t i;
	//cli();
	CANGCON = (1 << SWRES);
	CANGIE = (1 << ENIT) | (1 << ENRX) | (1 << ENTX) | (1 << ENERR);
	CANIE2 = (1 << IEMOB1);
	CANIE1 = 0;
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

void can_send(uint16_t id, uint8_t *data, uint8_t len)
{
	uint8_t i;
	CANPAGE = (1 << MOBNB0);
	CANIDT1 = id >> 3;
	CANIDT2 = (id & 0x07) << 5;
	CANIDT3 = 0x00;
	CANIDT4 = 0x00;
	CANIDM1 = 0x00;
	CANIDM1 = 0x00;
	CANIDM1 = 0x00;
	CANIDM1 = 0x00;
	for (i = 0; i < 8; i++)
		CANMSG = data[i];
	CANCDMOB = 0x40 | (len & 0x0F);	// enable transmission
	CANSTMOB = 0x00;
}
