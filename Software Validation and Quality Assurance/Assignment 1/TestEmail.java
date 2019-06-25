package org.apache.commons.mail;

import static org.junit.Assert.*;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.mail.BodyPart;
import javax.mail.MessagingException;
import javax.mail.Multipart;
import javax.mail.Session;
import javax.mail.internet.AddressException;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeBodyPart;
import javax.mail.internet.MimeMultipart;
import javax.naming.NamingException;

import org.junit.Rule;
import org.junit.Test;
import org.junit.rules.ExpectedException;

import junit.framework.TestCase;


public class TestEmail extends TestCase
{
	protected SimpleEmail email;

	@Override 
	protected void setUp() 
	{
		email = new SimpleEmail();
	}
	
	@Test
	public void testAddBcc() throws Exception 
	{
		List<InternetAddress> adresses = new ArrayList<InternetAddress>();
		
		adresses.add(new InternetAddress ("gogogoing@hotmail.com"));
		email.addBcc("gogogoing@hotmail.com");
		assertEquals(adresses, email.getBccAddresses());
		
		adresses.add(new InternetAddress ( "jonhouston2011@gmail.com"));
		adresses.add(new InternetAddress ("RescueCatLovesAnime@gmail.com"));
		adresses.add(new InternetAddress ("ladyoshino@gmail.com"));
		
		String[] address = new String[] {"jonhouston2011@gmail.com", "RescueCatLovesAnime@gmail.com", "ladyoshino@gmail.com"};
		email.addBcc(address);
		
		assertEquals(adresses, email.getBccAddresses());
	}
	
	@Test
	public void testAddCc() throws Exception
	{
		List<InternetAddress> testCc = new ArrayList<InternetAddress>();
		
		testCc.add(new InternetAddress("anotherEmail@yahoo.com"));
		
		email.addCc("anotherEmail@yahoo.com");
		
		assertEquals(testCc, email.getCcAddresses());
	}
	
	@Test
	public void testAddHeader() throws IllegalArgumentException
	{
		/*String headerNameTest = "Test Name";
		String headerValueTest = "Test Value";*/
		//Map<String,String> testHeader = new HashMap<String,String>();
		String valueIAE = "value can not be null or empty";
		String nameIAE = "name can not be null or empty";
		
		//Try Working Set
		email.addHeader("Test Name", "Test Value");
		
		//Try value empty
		try
		{
			email.addHeader("Test Name", null);
		}
		catch(IllegalArgumentException IAE)
		{
			assertTrue(IAE.getMessage().equals(valueIAE));
		}
		
		//Try name empty
		try
		{
			email.addHeader(null, "Test Value");
		}
		catch(IllegalArgumentException IAE)
		{
			assertTrue(IAE.getMessage().equals(nameIAE));
		}
	}
	
	@Test
	public void testAddReplyTo() throws EmailException, AddressException
	{
		List<InternetAddress> testList = new ArrayList<InternetAddress>();
		testList.add(new InternetAddress("onechanbara@live.com"));
		
		email.addReplyTo("onechanbara@live.com");
		
		assertEquals(testList,email.getReplyToAddresses());
	}
	
	
	@Test
	public void testBuildMimeMessage() throws EmailException, MessagingException
	{
		email.setHostName("fakehost");
		email.setFrom("rescuecattestemail@gmail.com");
		email.addTo("jonhouston2011@gmail.com");
		email.setSubject("alot about nothing");
		
		Multipart multipart = new MimeMultipart();
	    BodyPart messageBodyPart = new MimeBodyPart();
	    messageBodyPart.setText("certainly not null");
	    multipart.addBodyPart(messageBodyPart);
	    email.setContent((MimeMultipart) multipart);
	    

		
		email.buildMimeMessage();
		
		try
		{
			email.buildMimeMessage();
		}
		catch(IllegalStateException e)
		{
			assertTrue(e.getMessage().equals("The MimeMessage is already built."));
		}
	}
	
	@Test 
	public void testBuildMimeMessage2() throws EmailException
	{
		email.setHostName("fakehost");
		email.setFrom("rescuecattestemail@gmail.com");
		email.addTo("jonhouston2011@gmail.com");
		email.addHeader("nothing personal", "some value");
		email.addBcc("onemore@gmail.com");
		email.addCc("somethingsomething@yahoo.com");
		email.addReplyTo("canwaittofinish@gmail.com");
		email.setPopBeforeSmtp(true, "some fake host", "some fake username", "some fake password");
		
		try
		{
			email.buildMimeMessage();
		}
		catch(EmailException e)
		{
			assertFalse(e.getMessage().equals(""));
		}
	}
	
	@Test
	public void testGetHostName()
	{
		assertEquals(null, email.getHostName());
		
		email.setHostName("Test Host Name");
		assertEquals("Test Host Name", email.getHostName());
		
		email.setMailSession(Session.getInstance(System.getProperties()));
		assertEquals(null, email.getHostName());
	}
	
	@Test
	public void testGetMailSession() throws EmailException
	{
		
		
		String emailE = "Cannot find valid hostname for mail session";
		
		try
		{
			email.getMailSession();
		}
		catch(EmailException e)
		{
			assertTrue(e.getMessage().equals(emailE));
		}
		
		
		
		email.setAuthentication("Test String", "Test Password");
		
		try
		{
			email.setHostName("Test Host Name");
			email.getMailSession();
		}
		catch(EmailException e)
		{
			assertTrue(e.getMessage().equals(emailE));
		}
	}
	
	@Test
	public void testGetSentDate1()
	{
		Date testDate = new Date();
		assertEquals(email.getSentDate().compareTo(testDate), 0);
	}
	
	@Test
	public void testGetSentDate2()
	{
		Date testDate = new Date();
		email.setSentDate(testDate);
		assertEquals(email.getSentDate().compareTo(testDate),0);
	}
	
	@Test
	public void testGetSocketConnectionTimeout()
	{
		int testTimeoutTime = email.getSocketConnectionTimeout();
		assertEquals(testTimeoutTime, 60000); //default time 60 seconds = 60000 miliseconds
	}
	
	@Test
	public void testSend() throws EmailException, MessagingException
	{
		//Test Email Requirements for gmail
		email.setHostName("smtp.gmail.com");
		email.setSmtpPort(465);
		email.setSSL(true);
		email.setTLS(false);
		email.setFrom("rescuecattestemail@gmail.com");
		email.addTo("jonhouston2011@gmail.com");
		email.setAuthentication("rescuecattestemail@gmail.com", "jojoisthebest");
		
		assertEquals(email.send(), email.getMimeMessage().getMessageID());	
	}
	
	@Test
	public void testSetFrom() throws EmailException
	{
		assertEquals(email.setFrom("anotherfakeemail@avoidingthepuddle.com"), email);
	}
	
	@Test
	public void testUpdateContentType()
	{
		
		email.updateContentType("; charset= ASCII");
		email.updateContentType("; charset=");
		email.updateContentType(null);
		
		email.updateContentType("text/");
		
	}
	
	
}
