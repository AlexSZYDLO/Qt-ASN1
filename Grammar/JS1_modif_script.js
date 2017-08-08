a2.setBooleanValue(false);
b2.setEnumeratedValue(2);
c2.setIA5StringValue("alexandre_modif from script");
d2.setIntegerValue(-6500);
e2.setIgnoredByUser();
f2.setObjectIDValue("2.12.15632.875.1.625");
g2.setOctetStringValue("00112233445566778899aabbccddeeff00112233445566778899aabbccddeeff");
h2.setRealValue("523.325");
i2.setUTCTimeValue("9001031702+0100");
j2.setUTCTimeValue(91, 3, 11, 10, 30, 0, UTCTimeASN1.Plus, 1, 0);
k2.setUTF8StringValue("balbla");

seqof.clearDynamicData();
for (var integ = 0; integ < 10; integ++) {
	seqof.appendNewObject().setSelectedChoice(0).setBitStringValue('11111111');
}