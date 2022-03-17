package test;

import org.junit.Test;
import org.junit.Assert;
import static org.junit.Assert.assertEquals;

import Distance.Edit_Distance;

public class Edit_Distance_test{
	/*
	@Test
	public static void edit_distance_test(){
		Assert.assertTrue(Edit_Distance.edit_distance("casa","cassa")==1);
		Assert.assertTrue(Edit_Distance.edit_distance("casa","cara")==2);
		Assert.assertTrue(Edit_Distance.edit_distance("vinaio","vino")==2);
		Assert.assertTrue(Edit_Distance.edit_distance("tassa","passato")==4);
		Assert.assertTrue(Edit_Distance.edit_distance("pioppo","pioppo")==0);
	}
	*/
	@Test
	public void edit_distance_test(){
		assertEquals(1,Edit_Distance.edit_distance("casa","cassa"));
		assertEquals(2,Edit_Distance.edit_distance("casa","cara"));
		assertEquals(2,Edit_Distance.edit_distance("vinaio","vino"));
		assertEquals(4,Edit_Distance.edit_distance("tassa","passato"));
		assertEquals(0,Edit_Distance.edit_distance("pioppo","pioppo"));
		assertEquals(6,Edit_Distance.edit_distance("pazza","azzannata"));
	}

	@Test
	public void edit_distance_test_SP(){
		assertEquals(3,Edit_Distance.edit_distance("sesso","possesso"));
	}
	
	@Test
	public void edit_distance_test_PS(){
		assertEquals(3,Edit_Distance.edit_distance("possesso","sesso"));
		assertEquals(13,Edit_Distance.edit_distance("possesso","sessopiiiiiiiii"));
	}

	@Test
	public void edit_distance_dyn_test(){
		assertEquals(1,Edit_Distance.edit_distance_dyn("casa","cassa"));
		assertEquals(2,Edit_Distance.edit_distance_dyn("casa","cara"));
		assertEquals(2,Edit_Distance.edit_distance_dyn("vinaio","vino"));
		assertEquals(4,Edit_Distance.edit_distance_dyn("tassa","passato"));
		assertEquals(0,Edit_Distance.edit_distance_dyn("pioppo","pioppo"));
		assertEquals(3,Edit_Distance.edit_distance_dyn("perpeteva","perpetrava"));
	}

	@Test
	public void edit_distance_dyn_test_SP(){
		assertEquals(3,Edit_Distance.edit_distance_dyn("sesso","possesso"));
	}
	@Test
	public void edit_distance_dyn_test_PS(){
		assertEquals(3,Edit_Distance.edit_distance_dyn("possesso","sesso"));
		assertEquals(13,Edit_Distance.edit_distance_dyn("possesso","sessopiiiiiiiii"));
	}
}