/* Make a signed integer from latitude or longitude */
int32_t dmmtoint(char *str, char *hemi)
{
	// input format is DDDMM.MMMM
	int degrees;
	float minutes;
	int32_t r;
	if (str[5] == '.') {
		sscanf(str, "%3d%f", &degrees, &minutes);	// *FIXME* scanning minutes does not work
		minutes = atof(str + 3);
	} else {
		sscanf(str, "%2d%f", &degrees, &minutes);	// *FIXME* scanning minutes does not work
		minutes = atof(str + 2);
	}
	r = (60 * degrees + minutes) * 1000;
	if (hemi && (*hemi == 'S' || *hemi == 'W'))
		return (-1 * r);
	return (r);
}
