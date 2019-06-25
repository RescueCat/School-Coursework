package Model;

import java.time.LocalDate;

public class AuthorModel 
{
	private int aID;
	private String firstName;
	private String lastName;
	private LocalDate dateOfBirth;
	private String gender;
	private String webSite;
	
	public AuthorModel()
	{
		this.aID = 0;
		this.firstName = "default First";
		this.lastName = "default Last";
		this.dateOfBirth = LocalDate.of(2018, 12, 31);
		this.gender = "default Gender";
		this.webSite = "www.defaultwebsite.com";
	}
	
	//Setters
	public void setID(int id)
	{
		this.aID = id;
	}
	
	public void setFName(String name)
	{
		this.firstName = name;
	}
	
	public void setLName(String name)
	{
		this.lastName = name;
	}
	
	public void setDOB(LocalDate date)
	{
		//I'm sure some sort of conversion will be done here
		this.dateOfBirth = date;
	}
	
	public void setGender(String Gender)
	{
		this.gender = Gender;
	}
	
	public void setWeb(String site)
	{
		this.webSite = site;
	}
	
	//Getters
	public int getaID()
	{
		return aID;
	}
	
	public String getFName()
	{
		return firstName;
	}
	
	public String getLName()
	{
		return lastName;
	}
	
	public LocalDate getDOB()
	{
		return dateOfBirth;
	}
	
	public String getGender()
	{
		return gender;
	}
	
	public String getWeb()
	{
		return webSite;
	}
}

