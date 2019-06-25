
public class BookModel 
{
	private String theBookTitle;
	private String Author;
	private String ISBN;
	private String Publisher;
	private String imgURL;
	private String Summary;
	private String[] Book1 = {"Scott O'Dell","0545289599","HMH Books for Young Readers (2010)","src/Images/Island of The Blue Dolphins.jpg"};
	private String[] Book2 = {"Dr. Seuss","039480001X","Random House (1957)", "src/Images/The Cat in the Hat.jpg"};
	private String[] Book3 = {"Marcel Proust","9788893153812","Editions Grasset (1908)", "src/Images/In Search of Lost Time.jpg"};
	private String[] Book4 = {"Miguel de Cervantes","0060934344","Ecco (2005)", "src/Images/Don Quixote.jpg"};
	private String[] Book5 = {"James Joyce","1450523730","Public Domain Books (2009)", "src/Images/Ulysses.jpg"};
	
	private String[] Summaries = {"Far off the coast of California looms a harsh rock known as the island of San Nicholas. Dolphins flash in the blue waters around it, sea otter play in the vast kep beds, and sea elephants loll on the stony beaches.\r\n" + 
			"\r\n" + 
			"Here, in the early 1800s, according to history, an Indian girl spent eighteen years alone, and this beautifully written novel is her story. It is a romantic adventure filled with drama and heartache, for not only was mere subsistence on so desolate a spot a near miracle, but Karana had to contend with the ferocious pack of wild dogs that had killed her younger brother, constantly guard against the Aleutian sea otter hunters, and maintain a precarious food supply.\r\n" + 
			"\r\n" + 
			"More than this, it is an adventure of the spirit that will haunt the reader long after the book has been put down. Karana's quiet courage, her Indian self-reliance and acceptance of fate, transform what to many would have been a devastating ordeal into an uplifting experience. From loneliness and terror come strength and serenity in this Newbery Medal-winning classic.\r\n" + 
			"\r\n" + 
			"In celebration of the book's 50th anniversary, this edition has a stunning new look, and an introduction by Lois Lowry, Newbery Medal-winning author of The Giver and Number the Stars.", "Poor Dick and Sally. It's cold and wet and they're stuck in the house with nothing to do . . . until a giant cat in a hat shows up, transforming the dull day into a madcap adventure and almost wrecking the place in the process! Written by Dr. Seuss in 1957 in response to the concern that \"pallid primers [with] abnormally courteous, unnaturally clean boys and girls' were leading to growing illiteracy among children, The Cat in the Hat (the first Random House Beginner Book) changed the way our children learn how to read. ",
			"In Search of Lost Time follows the narrator's recollections of childhood and experiences into adulthood during late 19th century to early 20th century aristocratic France, while reflecting on the loss of time and lack of meaning to the world.[1] The novel began to take shape in 1909. Proust continued to work on it until his final illness in the autumn of 1922 forced him to break off. Proust established the structure early on, but even after volumes were initially finished he kept adding new material and edited one volume after another for publication. The last three of the seven volumes contain oversights and fragmentary or unpolished passages, as they existed only in draft form at the death of the author; the publication of these parts was overseen by his brother Robert.",
			"Hailed by Dostoyevsky as \"The final and greatest utterance of the human mind,\" Don Quixote constitutes a founding work of modern Western literature. Cervantes' masterpiece has been translated into more than sixty languages, and the novel's fantasy-driven \"knight,\" Don Quixote, and his loyal squire, Sancho Panza, rank among fiction's most recognized characters. Their adventures have been interpreted for film, opera, and ballet, and they head a cast of characters that comprises a diverse array of beliefs and perspectives, reflecting the historical realities of seventeenth-century Spain. \r\n" + 
			"Within its absorbing re-creation of the world during Cervantes' time, this parody of chivalric romances and epic of heroic idealism forms a strikingly contemporary narrative. The author is often credited with inventing the concept of the novel, addressing himself to the readers rather than the characters or the action. This edition of his landmark work presents the acclaimed 1755 Tobias Smollett translation.",
			"Banned in the United States until 1934 on account of its \"pornographic\" content, this controversial classic transforms a single day in Dublin into an experimental epic. James Joyce's psychological novel vividly re-creates the sights, sounds, smells, and voices of a June day in 1904 within a structure loosely based on Homer's Odyssey. Famed for the stream-of-consciousness technique that marked the beginning of modernist literature, the tale abounds in parodies, riddles, and sparkling wordplay. The long shadow it casts over subsequent novels has raised the suggestion that English-language fiction since 1922 has been a series of footnotes to Joyce's masterpiece.\r\n" + 
			"Few first editions generate more excitement among traders in rare books than Ulysses. Since the novel's debut, many experts have reinterpreted surviving drafts to produce revised texts, but this edition remains the one that Joyce himself reviewed and corrected prior to the initial publication. Thus, this volume represents the version truest to the author's vision."};
	
	public BookModel(String bookTitle) 
	{
		this.theBookTitle = bookTitle;
		
		if(this.theBookTitle == "Island of the Blue Dolphins")
		{
			setAuthor(Book1);
			setISBN(Book1);
			setPublisher(Book1);
			setImgUrl(Book1);
			setSumary(Summaries[0]);
		}
			
		if(this.theBookTitle == "The Cat in the Hat")
		{
			setAuthor(Book2);
			setISBN(Book2);
			setPublisher(Book2);
			setImgUrl(Book2);
			setSumary(Summaries[1]);
		}
		
		if(this.theBookTitle == "In Search of Lost Time")
		{
			setAuthor(Book3);
			setISBN(Book3);
			setPublisher(Book3);
			setImgUrl(Book3);
			setSumary(Summaries[2]);
		}
		if(this.theBookTitle == "Don Quixote")
		{
			setAuthor(Book4);
			setISBN(Book4);
			setPublisher(Book4);
			setImgUrl(Book4);
			setSumary(Summaries[3]);
		}
		if(this.theBookTitle == "Ulysses")
		{
			setAuthor(Book5);
			setISBN(Book5);
			setPublisher(Book5);
			setImgUrl(Book5);
			setSumary(Summaries[4]);
		}
		
	}

	private void setSumary(String stringSum)
	{
		this.Summary = stringSum;
	}

	//Setters
	private void setPublisher(String[] bookInfo) 
	{
		this.Publisher = bookInfo[2];
	}

	private void setISBN(String[] bookInfo) 
	{
		this.ISBN = bookInfo[1];
	}

	private void setAuthor(String[] bookInfo) 
	{
		this.Author = bookInfo[0];
	}
	
	public void setImgUrl(String[] bookInfo) 
	{
		
		this.imgURL = bookInfo[3];
	}
	
	//Getters
	public String getPublisher() 
	{
		return Publisher;
	}

	public String getISBN() 
	{
		return ISBN;	
	}

	public String getAuthor() 
	{
		return Author;	
	}

	public String getImgUrl() {
		
		return imgURL;
	}
	
	public String getSumary()
	{
		return Summary;
	}
}
