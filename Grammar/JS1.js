var defA = new BitStringASN1('def a');
defA.setBitStringValue('11');

var chCallBack = function(i) {
    if (i === 0) return new BitStringASN1('bitstring c1', '0A');
    if (i === 1) return new IntegerASN1('int c2', '0B');
    if (i === 2) return new RealASN1('real c3', '0C');
    if (i === 3) return new OctetStringASN1('octet string c4', '0D');
    if (i === 4) return new OctetStringASN1('octet string c5', '0E');
    if (i === 5) return new OctetStringASN1('octet string c6', '0F');
    if (i === 6) return new OctetStringASN1('octet string c7', '1A');
}

function MakeSeq1() { 
	var a1 = new BitStringASN1('bitstring a', '0A', false, false, defA);
	var b1 = new BitStringASN1('bitstring b', '0B', true, true);
	var c1 = new BitStringASN1('bitstring c', '0C');
	var ch1 = new ChoiceASN1(chCallBack, 7, 'theChoice', 'AA');
	return [a1, b1, c1, ch1];
}

var seq1 = new SequenceASN1(MakeSeq1(), 'Sequence 1', 'AA');

seq1.getObjectAt(0).setBitStringValue('1010'); 
seq1.getObjectAt(1).setBitStringValue('1000');
seq1.getObjectAt(1).setIgnoredByUser(true);
seq1.getObjectAt(2).setBitStringValue('001');
seq1.getObjectAt(3).setSelectedChoice(2);
var ttt = seq1.getObjectAt(3).getSelectedChoice();
ttt.setRealValue(5623.415);

var a2 = new BooleanASN1('bool', '0A');
var b2 = new EnumeratedASN1('enum', '0B');
var c2 = new IA5StringASN1('ia5 string', 'BFB900');
var d2 = new IntegerASN1('integer a', '0D');
var e2 = new NullASN1('null', '0E', true);
var f2 = new ObjectIDASN1('OID', '0F');
var g2 = new OctetStringASN1('octet string', '1A');
var h2 = new RealASN1('real', '1B');
var i2 = new UTCTimeASN1('utc time', '1C');
var j2 = new UTCTimeASN1('utc time', '1D');
var k2 = new UTF8StringASN1('utf8 string', '1E');

var arr2 = [a2, b2, c2, d2, e2, f2, g2, h2, i2, j2, k2];
var seq2 = new SetASN1(arr2, 'set 2', 'BB');

var seqofcallback = function() {
	//return new BitString('seqof bitstring');
    return new ChoiceASN1(chCallBack, 7, 'theChoice', 'AA');
}
var seqof = new SequenceOfASN1(seqofcallback, 'sequence of', 'CC');
seqof.appendNewObject().setSelectedChoice(0).setBitStringValue('11111111');
seqof.appendNewObject().setSelectedChoice(1);
seqof.appendNewObject().setSelectedChoice(2);
seqof.appendNewObject().setSelectedChoice(3);
seqof.getObjectAt(seqof.getSequenceOfSize() - 1).setSelectedChoice(0);

var mainarr = [seq1, seqof, seq2];
var mainseq = new SequenceASN1(mainarr, 'Main Seq', '');
mainseq.registerGrammar();

a2.setBooleanValue(true);
b2.setEnumeratedValue(4);
c2.setIA5StringValue("alexandre");
d2.setIntegerValue(-6500);
e2.setIgnoredByUser();
f2.setObjectIDValue("2.12.15632.875.1.625");
g2.setOctetStringValue("00112233445566778899aabbccddeeff");
h2.setRealValue("523.325");
i2.setUTCTimeValue("9001031702+0100");
j2.setUTCTimeValue(91, 3, 11, 10, 30, 0, UTCTimeASN1.Plus, 1, 0);
k2.setUTF8StringValue("szydlowski");

