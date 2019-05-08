/* EZNET SECS MESSAGE FORMAT FILE */

S1F1W.


S1F2
<L[0]>.


S1F2
<L[2]
  <A[20]  MDLN>
  <A[20]  SOFTREV>
>.


S1F3W
<L[n]
  <U2  SVID>
>.

S1F3W
<L[n]
  <U4  SVID>
>.

S1F4
<L[n]
	<VAR SV>
>.

S1F11W
<L[n]
  <U2  SVID>
>.

S1F11W
<L[n]
  <U4  SVID>
>.

S1F12
<L[n]
	<L
		<U4 SVID>
		<A[40] SVNAME>
		<A[40] UNIT>
	>
>.

S1F13W
<L[0]>.


S1F13W
<L[2]
  <A[20]  MDLN>
  <A[20]  SOFTREV>
>.


S1F14
<L[2]
  <B  COMMACK>
  <L[0]>
>.


S1F14
<L[2]
  <B  COMMACK>
  <L[2]
    <A[20]  MDLN>
    <A[20]  SOFTREV>
  >
>.


S1F15W.

S1F16
<B OFLACK>.

S1F17W.

S1F18
<B ONLACK>.

S2F13W
<L[n]
	<U2 ECID>
>.

S2F13W
<L[n]
	<U4 ECID>
>.

S2F14
<L[n]
	<VAR ECV>
>.

S2F15W
<L[n]
	<L
		<VAR  ECID>
		<VARIANT  ECV>
	>
>.

S2F16
<B EAC>.


S2F17W.

S2F18
<A[16] TIME>.

S2F23W
<L
	<VAR  TRID>
	<A[8]  DSPER>
	<VAR  TOTSMP>
	<VAR  REPGSZ>
	<L[n]
		<VAR  SVID>
	>
>.

S2F24
<B TIAACK>.

S2F25W
<B[n] ABS>.

S2F26
<B[n] ABS>.

S2F29W
<L[n]
	<VAR  ECID>
>.

S2F30
<L[n]
	<L
		<VAR ECID>
		<A[40] ECNAME>
		<VARIANT ECMIN>
		<VARIANT ECMAX>
		<VARIANT ECDEF>
		<A[40] UNIT>
	>
>.

S2F31W
<A[16]  TIME>.

S2F32
<B TIACK>.

S2F33W
<L
	<VAR  DATAID>
	<L
	>
>.

S2F33W
<L
	<VAR  DATAID>
	<L[n]
		<L
			<VAR  RPTID>
			<L[n]
				<VAR  VID>
			>
		>
	>
>.

S2F34
<B DRACK>.

S2F35W
<L
	<VAR DATAID>
	<L[n]
		<L
			<VAR  CEID>
			<L[n]
				<VAR  RPTID>
			>
		>
	>
>.

S2F36
<B LRACK>.

S2F37W
<L
	<BOOLEAN  CEED>
	<L[n]
		<VAR  CEID>
	>
>.

S2F38
<B ERACK>.


S2F41W
<L
	<A[40]  RCMD>
	<L[n]
		<L
			<A[40]  CPNAME>
			<VARIANT  CPVAL>
		>
	>
>.

S2F42
<L
	<B HCACK>
	<L[n]
		<L
			<A[40] CPNAME>
			<VARIANT CPACK>
		>
	>
>.

S2F43W
<L[n]
	<L
		<U1 STRID>
		<L[n]
			<U1 FCNID>
		>
	>
>.

S2F44
<L
	<B RSPACK>
	<L[n]
		<L
			<U1 STRID>
			<B STRACK>
			<L[n]
				<U1 FCNID>
			>
		>
	>
>.

S2F45W
<L[2]
	<U4 DATAID>
	<L[n]
		<L[2]
			<U4 VID>
			<L[n]
				<L[2]
					<B LIMITID>
					<L[n]
						<VARIANT DEADBAND>
					>
				>
			>
		>
	>
>.

S2F46
<L
	<B VLAACK>
	<L[n]
		<L
			<U4 VID>
			<B LVACK>
			<L>
		>
	>
>.

S2F46
<L
	<B VLAACK>
	<L[n]
		<L
			<U4 VID>
			<B LVACK>
			<L
				<B LIMITID>
				<B LIMITACK>
			>
		>
	>
>.

S2F47W
<L[n]
	<U4 VID>
>.

S2F48
<L[n]
	<L
		<U4 VID>
		<L>
	>
>.

S2F48
<L[n]
	<L
		<U4 VID>
		<L
			<A[40] UNIT>
			<VARIANT LIMITMIN>
			<VARIANT LIMITMAX>
			<L[n]
				<L
					<B LIMITID>
					<VARIANT UPPERDB>
					<VARIANT LOWERDB>
				>
			>
		>
	>
>.


S3F17W 
<L
	<U4 DATAID>
	<A[100]  PROCEEDWITHCARRIER>
	<A[100]  CARRIERID>
	<B  PTN>
	<L
		<L
			<A[100] CAPACITY>
			<B CAPACITY_NUMBER>
		>
		<L
			<A[100] SUBSTRATECOUNT>
			<B SUBSTRATECOUNT_NUMBER>
		>
		<L
			<A[100] CONTENTMAP>
			<L[N]
				<L
					<A[100] LOTID>
					<A[100] WAFERID>
				>
			>
		>
		<L
			<A[100] SLOTMAP>
			<L[N]
				<U1 SLOT_NUMBER>
			>
		>
		<L
			<A[100] USAGE>
			<A[100] PRODUCT>
		>
	>
>.

S3F17W 
<L
	<U4 DATAID>
	<A[100]  CANCELCARRIER>
	<A[100]  CARRIERID>
	<U1  PTN>
	<L
	>
>.

S3F18 
<L
	<U1 CAACK>
	<L[N]
		<L
			<VAR ERROR_CODE>
			<A[100] ERROR_TEXT>
		>
	>
>.
	


S5F1W
<L
	<B ALCD>
	<U4 ALID>
	<A[80] ALTX>
>.

S5F2
<B  ACKC5>.

S5F3W
<L
	<B  ALED>
	<U4[n]  ALID>
>.

S5F4
<B ACKC5>.

S5F5W
<U4[n]  ALID>.

S5F6
<L[n]
	<L
		<B ALCD>
		<U4 ALID>
		<A[80] ALTX>
	>
>.

S5F7W.

S6F1W
<L
	<U2 TRID>
	<U2 SMPLN>
	<A[16] STIME>
	<L[n]
		<VARIANT SV>
	>
>.

S6F2
<B  ACKC6>.


S6F11W
<L
	<U4 DATAID>
	<U4 CEID>
	<L[n]
		<L
			<U4 RPTID>
			<L[n]
				<VARIANT SV>
			>
		>
	>	
>.

S6F12
<B  ACKC6>.

S6F13W
<L
   <VAR DATID>
   <VAR CEID>
   <L
      <L[n]
         <VAR RPTID>
         <L[n]
            <VAR VID>
            <VAR V>
         >
      >
   >
>.

S6F14
<B ACK>.

S6F15W
<VAR  CEID>.

S6F16
<L
	<U4 DATAID>
	<U4 CEID>
	<L[n]
		<L
			<U4 RPTID>
			<L[n]
				<VARIANT SV>
			>
		>
	>
>.

S6F17W
<VAR CEID>.

S6F18
<L
   <VAR DATAID>
   <VAR CEID>
   <L[n]
      <L
         <VAR RPTID>
         <L[n]
            <VAR V>
         >
      >
   >
>.

S6F19W
<VAR  RPTID>.

S6F20
<L[n]
	<VARIANT V>
>.

S6F21W
<VAR RPTID>.

S6F22
<L[n]
   <L
      <VAR VID>
      <VAR V>
   >
>.

S6F23W
<U1 RSDC>.

S6F24
<B RSDA>.

S7F1W
<L
	<A[80] PPID>
	<VAR LENGTH>
>.

S7F2
<B PPGNT>.

S7F3W
<L
	<A[80] PPID>
	<B[n] PPBODY>
>.

S7F4
<B ACKC7>.

S7F5W
<A[80] PPID>.

S7F6
<L
	<A[80] PPID>
	<B[n] PPBODY>
>.

S7F17W
<L[n]
   <A[50] PPID>
>.

S7F18
<B ACK>.

S7F19W.

S7F20
<L[n]
	<A[80] PPID>
>.


S7F23W
<L
   <A[50] PPID>
   <A[50] MLDN>
   <A[50] SOFTREV>
   <L[n]
	<L
      		<A[50] CCODE>
      		<L
         		<VAR PPARM>
      		>
	>
   >
>.

S7F24
<B ACKC7>.


S7F25W
<A[50] PPID>.

S7F26
<L
   <A[50] PPID>
   <A[50] MLDN>
   <A[50] SOFTREV>
   <L
      <A[50] CCODE>
      <L[n]
         <VAR PPARM>
      >
   >
>.

S9F1
<B[10] MHEAD>.

S9F3
<B[10] MHEAD>.

S9F5
<B[10] MHEAD>.

S9F7
<B[10] MHEAD>.

S9F9
<B[10] MHEAD>.

S9F11
<B[10] MHEAD>.

S9F13
<L
   <A[80] MEXP>
   <A[80] EDID>
>.

S10F1W
<L
   <B TID>
   <A[80] TEXT>
>.

S10F1
<L
   <B TID>
   <A[80] TEXT>
>.

S10F2
<B ACK>.

S10F3W
<L
	<B  TID>
	<A[200]  TEXT>
>.

S10F4
<B ACKC10>.

S10F5W
<L
	<B  TID>
	<L[n]
		<A[80]  TEXT>
	>
>.

S10F6
<B ACKC10>.

S14F3W
<L
   <A[50] OBJ_SPEC>
   <A[50] OBJ_TYPE>
   <L[n] 
   	  <A[40] OBJ_ID>      
   > 	
   <L[n] 
	  <L
   	     <A[40] ATTR_ID>   
	     <A[10000] ATTR_VALUE>   
          >  
   >
>.

S14F4
<L
           <L[n]
                     <L
                                <A[40] OBJID>
                                <L[n]
                                           <L[2]
                                                     <A[50] ATTRID>
                                                     <A[50] ATTRDATA>
                                           >
                                >
                     >
           >
           <L
                     <U1 OBJACK_0_OK_1_ERROR>
                     <L[n]
                                <L
                                           <VAR ERRORCODE>
                                           <A[100] ERROR_TEXT>
                                >
                     >
           >
>.