package Distance;

import java.lang.Math;

public class Edit_Distance{

	public static int edit_distance(String s1, String s2){
		if(s1.isEmpty()){
			return s2.length();
		}
		if(s2.isEmpty()){
			return s1.length();
		}
		if(Character.toUpperCase(s1.charAt(0))==Character.toUpperCase(s2.charAt(0))){
			return edit_distance(s1.substring(1), s2.substring(1));
		}else{
			return Math.min(1 + edit_distance(s1, s2.substring(1)), 1 + edit_distance(s1.substring(1), s2));
		}
	}

	public static int edit_distance_dyn(String s1, String s2){
		int[][] c = new int[s1.length()+1][s2.length()+1];
		for (int i=0; i<s2.length()+1;i++ ) {
			c[0][i]=0;
		}
		for (int i=0; i<s1.length()+1;i++ ) {
			c[i][0]=0;
		}
		LCS_BU(s1,s2,c,1,1);
		int x=c[s1.length()][s2.length()];
		return (s2.length()-x)+(s1.length()-x);
	}
	public static void LCS_BU(String s1, String s2, int[][] c,int i,int j){
		if(Character.toUpperCase(s1.charAt(i-1))==Character.toUpperCase(s2.charAt(j-1))){
			c[i][j]=c[i-1][j-1]+1;
		}else{
			if(c[i-1][j]>=c[i][j-1]){
				c[i][j]=c[i-1][j];
			}else{
				c[i][j]=c[i][j-1];
			}
		}

		if(j<s2.length()){
			LCS_BU(s1,s2,c,i,j+1);
		}else if(i<s1.length()){
			LCS_BU(s1,s2,c,i+1,1);
			
		}
	}
}