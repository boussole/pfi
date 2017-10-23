<?php
/**
 * ����� ����������� ��� �������� �� ���c��������
 * 
 */
//--------------------------------------------------------------------------
require_once('dmoztopic/dmoztopicclass.php');
require_once('dmozsite/dmozsiteclass.php');
require_once('tagarray/tagarrayclass.php');
require_once('logfile/logfileclass.php');
//-
require_once('parserdefine.php');
//--------------------------------------------------------------------------
//
class TParser
{
	// ������ ������� � �������� (���������)
	private $TempDmozTopicArray;
	// ������ ������� � ������� (���������)
	private $TempDmozSiteArray;
	// ������ ���� �����������
	private $TagArray;
	//-
	// ��������� ������� ������� � �������� (���������)
	private $TempDmozTopic = null;
	// ��������� ������� ������� � ������ (���������)
	private $TempDmozSite = null;
	// ��� ����, ���� � ������� ���� ������ ����������, ����������� �� ���� ������������
	private $LogFile = null;
	//-
	// ���������� �������
	private $XMLParser;
	// ���� ���� ������
	private $FileHandler;
	//-
	// ���������� ��������� dmoz_topic
	private $DmozTopicCount = 0;
	// ���������� ��������� dmoz_sites
	private $DmozSitesCount = 0;
	//-
	// ���� �������
	private $MaxTopicRang = 0;
	//-----------------------------------------------------------------------
	/**
	 * �����������
	 * �������� ���� ����������� ��������
	 */
	public function __construct($filename)
	{
		$filename = trim((string)$filename);
		if (($filename != "") && (($this->FileHandler = fopen($filename, "r")) != null))
		{		
			// ������� ����� ������ �� ���������� ������
			truncateTable("temp_dmoz_topics");
			//deleteTable("temp_dmoz_topics");
			//alterTable("temp_dmoz_topics AUTO_INCREMENT = 1");
			//-
			truncateTable("temp_dmoz_sites");
			//deleteTable("temp_dmoz_sites");
			//alterTable("temp_dmoz_sites AUTO_INCREMENT = 1");
			//-
			truncateTable("dmoz_topics");
			//-
			truncateTable("dmoz_sites");
			//-
			$this->TempDmozTopicArray = array();
			$this->TempDmozSiteArray = array(array());
			//-
			$this->TagArray = new TTagArray();
			$this->LogFile = new TLogFile();
			//------------------------------
			$this->XMLParser = xml_parser_create();
			xml_set_element_handler($this->XMLParser, array($this, 'TagOpen'), array($this, 'TagClose'));
			xml_parser_set_option($this->XMLParser, XML_OPTION_CASE_FOLDING, false);
			xml_set_character_data_handler($this->XMLParser, array($this, 'TagContain'));
			$this->MaxTopicRang = 0;
		}
		else
		{
			throw new Exception(FILE_NAME_ERROR);
		}
	}
	//-----------------------------------------------------------------------
	/**
	 * ����������
	 * ������������, ���� ���������� ������, ��������
	 */
	public function __destruct()
	{
		//------------------------------
		//�������� � ���� ��� ���������� ��������� �� �������� � ��������� ����� � ������ ������
		//...
		//------------------------------
		unset($this->TempDmozTopicArray);
		unset($this->TempDmozSiteArray);
		unset($this->TempDmozTopic);
		unset($this->TempDmozSite);
		unset($this->TagArray);
		unset($this->LogFile);
		//-
		xml_parser_free($this->XMLParser);
		fclose($this->FileHandler);
	}
	//-----------------------------------------------------------------------
	/**
	 * ������� - ���������� ������� "�������� ����"
	 *
	 * @param int $parser
	 * @param string $name
	 * @param string array $attrs
	 */
	private function TagOpen($parser, $name, $attrs)
	{
		global $NameIndex;
		$result = true;
		if (!$this->TagArray->GetIgnoreFlag())
		{
			$stringnumber = xml_get_current_line_number($parser);
			switch (GetNameIndex($name))
			{	// � �����
				case $NameIndex[TAG_ROOT]: 
					{
						$result = $this->TestRootTag($parser, $name, $attrs, $stringnumber);
						break;
					}
				// � RF
				case $NameIndex[TAG_TOPIC]:
					{
						$result = $this->TestTopicRubricTag($parser, $name, $attrs, $stringnumber);
						break;
					}
				// � Topic
				case $NameIndex[TAG_CATID]:				
					{
						$result = false;
						break;
					}
														
				// � Topic
				case $NameIndex[TAG_LINK]:				
					{
						$result = $this->TestLinkTag($parser, $name, $attrs, $stringnumber);
						break;
					}
				// � RDF
				case $NameIndex[TAG_EXPAGE]:			
					{
						$result = $this->TestExternalPageTag($parser, $name, $attrs, $stringnumber);
						break;
					}
				// � External page
				case $NameIndex[TAG_EXPAGE_TITLE]:		
					{
						$result = $this->TestExternalPageTitleTag($parser, $name, $attrs, $stringnumber);
						break;
					}
				// � External page	
				case $NameIndex[TAG_EXPAGE_DESCRIPTION]:
					{
						$result = $this->TestExternalPageDescriptionTag($parser, $name, $attrs, $stringnumber);
						break;
					}
				// � External page
				case $NameIndex[TAG_EXPAGE_TOPIC]:
					{
						$result = $this->TestExternalPageTopicTag($parser, $name, $attrs, $stringnumber);
						break;
					}
				// � External page
				case $NameIndex[TAG_PRIORITY]:
					{
						$result = false;
						break;
					}														
				// ����������� ���
				default:
					{								
						$result = $this->UnknownTag($parser, $name, $attrs, $stringnumber);
						break;
					}
			}
		}
		else 
		{
			$this->LogFile->Write(sprintf(IGNORE_WARNING . "\n", $name, xml_get_current_line_number($parser)));
		}
		$this->TagArray->AddTag($name, $result === false);
	}
	//-----------------------------------------------------------------------
	/**
	 * ������� - ���������� ������� "�������� ����"
	 *
	 * @param int $parser
	 * @param string $name
	 */
	private function TagClose($parser, $name)
	{
		if (!$this->TagArray->GetIgnoreFlag())
		{
			global $NameIndex;
			switch (GetNameIndex($name))
			{
				case $NameIndex[TAG_TOPIC]:
					{		
						$this->AddTopicTagInfo();
						break;
					}
				case $NameIndex[TAG_EXPAGE]:
					{
						$this->AddExPageTagInfo();
						break;	
					}
				case $NameIndex[TAG_LINK]:
					{
						$this->AddLinkTagInfo();
						unset($this->TempDmozSite);
						break;
					}
			}
		}
		$this->TagArray->RemoveTag();
	}
	//------------------------------------------------------------------------
	/**
	 * �������, ����������� ������� �������� ���������� ����
	 *
	 * @param int $parser
	 * @param string $content
	 */
	private function TagContain($parser, $content)
	{
		if (!$this->TagArray->GetIgnoreFlag())
		{
			global $NameIndex;
			switch (GetNameIndex($this->TagArray->GetTag()))
			{
				case $NameIndex[TAG_EXPAGE_TITLE]:
					{	
						$this->TestExPageTitleContent($content);
						break;
					}
				case $NameIndex[TAG_EXPAGE_DESCRIPTION]:
					{
						$this->TestExPageDescriptionContent($content);
						break;
					}
				case $NameIndex[TAG_EXPAGE_TOPIC]:
					{
						$this->TestExPageTopicContent($content);
						break;
					}
			}
		}
	}
	//------------------------------------------------------------------------
	/**
	 * ������ ������ �������
	 *
	 */
	public function Start()
	{
		while ($data = fread($this->FileHandler, 4096)) 
		{
	    	if (!xml_parse($this->XMLParser, $data, feof($this->FileHandler))) 
	    	{
	    		$error = sprintf(PARSE_ERROR . " %s at line %d\n", 
	    									xml_error_string(xml_get_error_code($this->XMLParser)), 
	    									xml_get_current_line_number($this->XMLParser));
	    		$this->LogFile->Write($error);
	    		throw new Exception($error, 0);
	    	}
		}
		// �������� ���������� ������ �� ���� � ���� ������
		$this->SyncDmozTopic();
		$this->SyncDmozSites();
		$this->testTempDmozTopics();
		$this->testTempDmozSites();
		// ������� ��������� ������
		truncateTable("temp_dmoz_topics");
		truncateTable("temp_dmoz_sites");
	}
	//------------------------------------------------------------------------
	/**
	 * �������� ��������� ���� RDF. ����� ����� ���� �� ������� ������� �� ������ ���� ������
	 *
	 * @param int $parser
	 * @param string $name
	 * @param string array $attrs
	 * @param int $stringnumber
	 * 
	 * @return bool - ��������� ��������
	 */
	private function TestRootTag($parser, $name, $attrs, $stringnumber)
	{
		if ($this->TagArray->GetCounter() > 0)
		{
			$this->LogFile->Write(sprintf(ROOT_WARNING . "\n" . IGNORE_WARNING . "\n", $stringnumber, $name, $stringnumber));
			return false;
		}
		return true;
	}
	//------------------------------------------------------------------------
	/**
	 * �������� ���� ������� Topic. ������ ��� ����� ��������� ������ ��� ������ RDF.
	 *
	 * @param int $parser
	 * @param string $name
	 * @param string array $attrs
	 * @param int $stringnumber
	 * 
	 * @return bool
	 */
	private function TestTopicRubricTag($parser, $name, $attrs, $stringnumber)
	{
		if ((strcmp($this->TagArray->GetTag(), TAG_ROOT)) !== 0)
		{
			$this->LogFile->Write(sprintf(STRUCT_WARNING . "\n" . IGNORE_WARNING . "\n", TAG_TOPIC, TAG_ROOT, $stringnumber, $name, $stringnumber));
			return false;
		}
		return $this->TestTopicAttr($parser, $name, $attrs, $stringnumber);	
	}
	//------------------------------------------------------------------------
	/**
	 * �������� ���� link (������). ������ ��� ����� ��������� ������ � ���� ������� (Topic).
	 *
	 * @param int $parser
	 * @param string $name
	 * @param string array $attrs
	 * @param int $stringnumber
	 * 
	 * @return bool
	 */
	private function TestLinkTag($parser, $name, $attrs, $stringnumber)
	{
		if (strcmp($this->TagArray->GetTag(), TAG_TOPIC) !== 0)
		{
			$this->LogFile->Write(sprintf(STRUCT_WARNING . "\n" . IGNORE_WARNING . "\n", TAG_LINK, TAG_TOPIC, $stringnumber, $name, $stringnumber));
			return false;
		}
		return $this->TestLinkAttr($parser, $name, $attrs, $stringnumber);
	}
	//------------------------------------------------------------------------
	/**
	 * �������� ���� External Page. ������ ��� ����� ��������� ������ ��� ������ RDF
	 *
	 * @param int $parser
	 * @param string $name
	 * @param string array $attrs
	 * @param int $stringnumber
	 * 
	 * @return bool
	 */
	private function TestExternalPageTag($parser, $name, $attrs, $stringnumber)
	{
		if (strcmp($this->TagArray->GetTag(), TAG_ROOT) !== 0)
		{
			$this->LogFile->Write(sprintf(STRUCT_WARNING . "\n" . IGNORE_WARNING . "\n", TAG_EXPAGE, TAG_ROOT, $stringnumber, $name, $stringnumber));
			return false;
		}
		return $this->TestExPageAttr($parser, $name, $attrs, $stringnumber);
	}
	//------------------------------------------------------------------------
	/**
	 * �������� ���� title. ������ ��� ����� ��������� ������ � ���� (External Page)
	 *
	 * @param int $parser
	 * @param string $name
	 * @param string array $attrs
	 * @param int $stringnumber
	 * 
	 * @return bool
	 */
	private function TestExternalPageTitleTag($parser, $name, $attrs, $stringnumber)
	{
		if (strcmp($this->TagArray->GetTag(), TAG_EXPAGE) !== 0)
		{
			$this->LogFile->Write(sprintf(STRUCT_WARNING . "\n" . IGNORE_WARNING . "\n", TAG_EXPAGE_TITLE, TAG_EXPAGE, $stringnumber, $name, $stringnumber));
			return false;
		}
		return true;
	}
	//------------------------------------------------------------------------
	/**
	 * �������� ���� description. ������ ��� ����� ��������� ������ � ���� (External Page)
	 *
	 * @param int $parser
	 * @param string $name
	 * @param string array $attrs
	 * @param int $stringnumber
	 * 
	 * @return bool
	 */
	private function TestExternalPageDescriptionTag($parser, $name, $attrs, $stringnumber)
	{
		if (strcmp($this->TagArray->GetTag(), TAG_EXPAGE) !== 0)
		{
			$this->LogFile->Write(sprintf(STRUCT_WARNING . "\n" . IGNORE_WARNING . "\n", TAG_EXPAGE_DESCRIPTION, TAG_EXPAGE, $stringnumber, $name, $stringnumber));
			return false;
		}
		return true;
	}
	//------------------------------------------------------------------------
	/**
	 * �������� ���� topic. ������ ��� ����� ��������� ������ � ���� (External Page)
	 *
	 * @param int $parser
	 * @param string $name
	 * @param string array $attrs
	 * @param int $stringnumber
	 * 
	 * @return bool
	 */
	private function TestExternalPageTopicTag($parser, $name, $attrs, $stringnumber)
	{
		if (strcmp($this->TagArray->GetTag(), TAG_EXPAGE) !== 0)
		{
			$this->LogFile->Write(sprintf(STRUCT_WARNING . "\n" . IGNORE_WARNING . "\n", TAG_EXPAGE_TOPIC, TAG_EXPAGE, $stringnumber, $name, $stringnumber));
			return false;
		}
		return true;
	}
	
	//------------------------------------------------------------------------
	/**
	 * ������ ����������� ���
	 *
	 * @param int $parser
	 * @param string $name
	 * @param string array $attrs
	 * @param int $stringnumber
	 * 
	 * @return bool
	 */
	private function UnknownTag($parser, $name, $attrs, $stringnumber)
	{
		$this->LogFile->Write(sprintf(UKNOWN_WARNING . "\n" . IGNORE_WARNING . "\n", $name, $stringnumber, $name, $stringnumber));
		return false;
	}
	//------------------------------------------------------------------------
	/**
	 * �������� ��������� ���� Topic
	 *
	 * @param int $parser
	 * @param string $name
	 * @param string array $attrs
	 * @param int $stringnumber
	 * @return bool
	 */
	private function TestTopicAttr($parser, $name, $attrs, $stringnumber)
	{
		$returnvalue = false;
		if (isset($attrs[ATTR_R_ID]))
		{
			$returnvalue = $this->TestRubricName($attrs[ATTR_R_ID], $stringnumber);
		}
		else 
		{
			$this->LogFile->Write(sprintf(ATTRIB_WARNING . "\n" . IGNORE_WARNING . "\n", ATTR_R_ID, $name, $stringnumber, $name, $stringnumber));
		}
		return $returnvalue;
	}
	//------------------------------------------------------------------------
	/**
	 * �������� ��������� ���� External Page
	 *
	 * @param int $parser
	 * @param string $name
	 * @param string array $attrs
	 * @param int $stringnumber
	 * @return bool
	 */
	private function TestExPageAttr($parser, $name, $attrs, $stringnumber)
	{
		$returnvalue = false;
		if (isset($attrs[ATTR_ABOUT]))
		{
			$attrs[ATTR_ABOUT] = trim($attrs[ATTR_ABOUT], " \t\r\n/");
			$this->TempDmozSite = new TTempDmozSite();
			$this->TempDmozSite->SetURL($attrs[ATTR_ABOUT]);
			$returnvalue = true;
		}
		else 
		{
			$this->LogFile->Write(sprintf(ATTRIB_WARNING . "\n" . IGNORE_WARNING . "\n", ATTR_ABOUT, $name, $stringnumber, $name, $stringnumber));
		}
		return $returnvalue;
	}
	//------------------------------------------------------------------------
	/**
	 * �������� ��������� ���� link
	 *
	 * @param int $parser
	 * @param string $name
	 * @param string array $attrs
	 * @param int $stringnumber
	 * @return bool
	 */
	private function TestLinkAttr($parser, $name, $attrs, $stringnumber)
	{
		$returnvalue = false;
		if (isset($attrs[ATTR_R_RESOURCE]))
		{
			$attrs[ATTR_R_RESOURCE] = trim($attrs[ATTR_R_RESOURCE], " \t\r\n/");
			$this->TempDmozSite = new TTempDmozSite();
			$this->TempDmozSite->SetTopicName($this->TempDmozTopic->GetTopicName());
			$this->TempDmozSite->SetRang($this->TempDmozTopic->GetRang());
			$this->TempDmozSite->SetTopicResolv(true);
			$this->TempDmozSite->SetURL($attrs[ATTR_R_RESOURCE]);
			$returnvalue = true;
		}
		else 
		{
			$this->LogFile->Write(sprintf(ATTRIB_WARNING . "\n" . IGNORE_WARNING . "\n", ATTR_R_RESOURCE, $name, $stringnumber, $name, $stringnumber));
			$returnvalue = false;
		}
		return $returnvalue;
	}
	//------------------------------------------------------------------------
	/**
	 * �������� ������������ ����� ������� (������ ���� �� ����� � �� ��������� ��� � ����� ������ ������ /)
	 *
	 * @param string $rubricname
	 * @return bool
	 */
	private function TestRubricName($rubricname, $stringnumber)
	{
		$rubricname = trim($rubricname, " \t\r\n/");
		$returnvalue = false;
		// ��� ������� �����������
		if (($rubricname != "") && (!$this->DoubleSlash($rubricname)) )
		{	
			// ��������, ����� � ����� ������ ��� ����������
			//if (isset($this->TempDmozTopicArray[$rubricname])) //&& � ���� ������
			//{
			//	$this->LogFile->Write(sprintf(RUBRIC_NAME_COLIS . "\n", $rubricname, $stringnumber));
			//}
			//else
			//{
				$this->TempDmozTopic = new TTempDmozTopic();
				$this->TempDmozTopic->SetTopicName($rubricname);
				$this->TempDmozTopic->SetParentName($this->GetParentRubricName($rubricname));
				$this->TempDmozTopic->SetRang($this->GetRang($rubricname));
				unset($TempDmozTopic);
				$returnvalue = true;
			//}
		}
		else
		{
			$this->LogFile->Write(sprintf(NAME_WARNING . "\n", $rubricname, $stringnumber));
		}
		return $returnvalue;
	}
	//------------------------------------------------------------------------
	/**
	 * ������� ����� ������������ �������
	 *
	 * @param string $rubricname
	 * @return string
	 */
	private function GetParentRubricName($rubricname)
	{
		$parentrubricname = "";
		if (($rubricname = trim((string)$rubricname)) != "")
		{
			$pattern = '/^(.*)\/.*$/';
			$temp = array();
			preg_match($pattern, $rubricname, $temp);
			$parentrubricname = $temp[1];
		}
		return $parentrubricname;
	}
	//------------------------------------------------------------------------
	/**
	 * ������� ����� ����������� �������
	 *
	 * @param string $rubricname
	 * @return int
	 */
	private function GetRang($rubricname)
	{
		$rang = 1;
		$rubricname = trim((string)$rubricname);
		for ($i = 0; $i < strlen($rubricname); $i++)
		{
			if ($rubricname[$i] == '/')
			{
				$rang++;
			}
		}
		return $rang;
	}
	//------------------------------------------------------------------------
	/**
	 * ����� ���� ������ ������ � �������� ����������� �������� (/)
	 *
	 * @param string $name
	 * @param string[1] $symbol
	 * @return bool
	 */
	private function DoubleSlash($rubricname, $symbol = '/')
	{
		$rubricname = trim($rubricname, " \t\r\n/");
		for ($i = 0; $i < strlen($rubricname); $i++)
		{
			if (($rubricname[$i] == $symbol) && ($i + 1 != strlen($rubricname)) && ($rubricname[$i] == $rubricname[$i + 1]))
			{
				return true;
			}
		}
		return false;
	}
	//------------------------------------------------------------------------
	/**
	 * �������� � ���������� ����������� ���� title (�������������� �������)
	 *
	 * @param string $content
	 */
	private function TestExPageTitleContent($content)
	{
		if (($content = trim($content)) != "")
		{
			if ($this->TempDmozSite->GetTitle() == "")
			{
				$this->TempDmozSite->SetTitle($content);
			}
			else 
			{
				$this->LogFile->Write(sprintf(CONTENT_EXIST . "\n", TAG_EXPAGE_TITLE, TAG_EXPAGE));
			}
		}
		else 
		{
			$this->LogFile->Write(sprintf(CLEAR_CONTENT_WARNING . "\n", TAG_EXPAGE_TITLE, $content));
		}
	}
	//------------------------------------------------------------------------
	/**
	 * �������� � ���������� ����������� ���� description (�������������� �������)
	 *
	 * @param string $content
	 */
	private function TestExPageDescriptionContent($content)
	{
		if (($content = trim($content)) != "")
		{
			if ($this->TempDmozSite->GetPassage() == "")
			{
				$this->TempDmozSite->SetPassage($content);
			}
			else 
			{
				$this->LogFile->Write(sprintf(CONTENT_EXIST . "\n", TAG_EXPAGE_DESCRIPTION, TAG_EXPAGE));
			}
		}
		else 
		{
			$this->LogFile->Write(sprintf(CLEAR_CONTENT_WARNING . "\n", TAG_EXPAGE_DESCRIPTION, $content));
		}
	}
	//------------------------------------------------------------------------
	/**
	 * �������� � ���������� ����������� ���� topic
	 *
	 * @param string $content
	 */
	private function TestExPageTopicContent($content)
	{
		$content = trim($content, " \t\r\n/");
		if (($content != "") && (!$this->DoubleSlash($content)))
		{
			if ($this->TempDmozSite->GetTopicName() == "")
			{
				$this->TempDmozSite->SetTopicName($content);
				$this->TempDmozSite->SetExpageResolv(true);
				$this->TempDmozSite->SetRang($this->GetRang($content));
			}
			else 
			{
				$this->LogFile->Write(sprintf(CONTENT_EXIST . "\n", TAG_EXPAGE_TOPIC, TAG_EXPAGE));
			}
		}
		else 
		{
			$this->LogFile->Write(sprintf(CLEAR_CONTENT_WARNING . "\n", TAG_EXPAGE_TOPIC, $content));			
		}
		$this->TagArray->SetIgnoreFlag();
	}
	//------------------------------------------------------------------------
	/**
	 * ��������� �� �������� � �������� ���������� � ������� � ���� ������
	 *
	 */
	private function AddTopicTagInfo()
	{
		global $DmozTopicMaxCount;
		if (
			(isset($this->TempDmozTopicArray[$this->TempDmozTopic->GetTopicName()])) 
			|| 
			(mysql_num_rows(selectData("* FROM temp_dmoz_topics WHERE topic_name = '" . mysql_real_escape_string($this->TempDmozTopic->GetTopicName()) . "'")) != 0))
		{
			$this->LogFile->Write(sprintf(RUBRIC_EXIST . "\n", $this->TempDmozTopic->GetTopicName()));
		}
		else
		{
			$this->TempDmozTopicArray[$this->TempDmozTopic->GetTopicName()] = $this->TempDmozTopic;
			$this->DmozTopicCount++;
			if ($this->DmozTopicCount >= $DmozTopicMaxCount)
			{
				$this->SyncDmozTopic();
			}
		}
		unset($this->TempDmozTopic);
	}
	//------------------------------------------------------------------------
	/**
	 * ���������� ���������� � ���� External page � ���
	 *
	 */
	private function AddExPageTagInfo()
	{
		global $DmozSitesMaxCount;
		if (trim($this->TempDmozSite->GetTopicName(), " \t\r\n/") != "")
		{
			// ������������ � ����
			$tempelement = $this->TempDmozSiteArray[$this->TempDmozSite->GetURL()][$this->TempDmozSite->GetTopicName()];
			$request = selectData("* FROM temp_dmoz_sites where topic_name='" . mysql_real_escape_string($this->TempDmozSite->GetTopicName()) . 
												"' AND url='" . mysql_real_escape_string($this->TempDmozSite->GetURL()) . "'");
			if (isset($tempelement))
			{
				if (!$tempelement->GetExpageResolv())
				{
					$tempelement->SetTitle($this->TempDmozSite->GetTitle());
					$tempelement->SetPassage($this->TempDmozSite->GetPassage());
					$tempelement->SetExpageResolv(true);
				}
				else
				{
					$this->LogFile->Write(sprintf(EXPAGE_EXIST . "\n", $tempelement->GetURL(), $tempelement->GetTopicName()));
				}
			}
			// ������������ � ����
			elseif (mysql_num_rows($request) != 0)
			{
				$tempobject = mysql_fetch_object($request);
				if (!$tempobject->expage_resolv)
				{
					updateTable("temp_dmoz_sites SET title='" . mysql_real_escape_string($this->TempDmozSite->GetTitle()) . 
							"', passage='" . mysql_real_escape_string($this->TempDmozSite->GetPassage()) .
							"', expage_resolv=" . true . " WHERE temp_site_id=" . $tempobject->temp_site_id);
				}
				else
				{
					$this->LogFile->Write(sprintf(EXPAGE_EXIST . "\n", $tempobject->url, $tempobject->topic_name));
				}
			}
			// �����������
			else
			{
				$this->TempDmozSiteArray[$this->TempDmozSite->GetURL()][$this->TempDmozSite->GetTopicName()] = $this->TempDmozSite;
				$this->DmozSitesCount++;
				if ($this->DmozSitesCount >= $DmozSitesMaxCount)
				{
					$this->SyncDmozSites();	
				}
			}
		}
		else
		{
			$this->LogFile->Write(sprintf(RUBRIC_NAME_MISS . "\n", TAG_EXPAGE));
		}
		unset($this->TempDmozSite);
	}
	//------------------------------------------------------------------------
	/**
	 * ���������� ���������� �� ���� link  � ���
	 *
	 */
	private function AddLinkTagInfo()
	{
		if (trim($this->TempDmozSite->GetTopicName(), " \t\r\n/") != "")
		{
			// ������������ � ����
			$tempelement = $this->TempDmozSiteArray[$this->TempDmozSite->GetURL()][$this->TempDmozSite->GetTopicName()];
			$request = selectData("* FROM temp_dmoz_sites where topic_name='" . mysql_real_escape_string($this->TempDmozSite->GetTopicName()) . 
										"' AND url='" . mysql_real_escape_string($this->TempDmozSite->GetURL()) . "'");
			if (isset($tempelement))
			{
				if (!$tempelement->GetTopicResolv())
				{
					$tempelement->SetTopicResolv(true);
				}
				else
				{
					$this->LogFile->Write(sprintf(LINK_EXIST . "\n", $tempelement->GetURL(), $tempelement->GetTopicName()));
				}
			}
			// ������������ � ����
			elseif (mysql_num_rows($request) != 0)
			{
				$tempobject = mysql_fetch_object($request);
				if (!$tempobject->topic_resolv)
				{
					updateTable("temp_dmoz_sites SET topic_resolv=" . true . " WHERE temp_site_id=" . $tempobject->temp_site_id);
				}
				else
				{
					$this->LogFile->Write(sprintf(LINK_EXIST . "\n", $tempobject->url, $tempobject->topic_name));
				}
			}
			// �����������
			else
			{
				$this->TempDmozSiteArray[$this->TempDmozSite->GetURL()][$this->TempDmozSite->GetTopicName()] = $this->TempDmozSite;
				$this->DmozSitesCount++;
				if ($this->DmozSitesCount >= $DmozSitesMaxCount)
				{
					$this->SyncDmozSites();	
				}
			}	
		}
		else
		{
			$this->LogFile->Write(sprintf(RUBRIC_NAME_MISS . "\n", TAG_LINK));
		}
		unset($this->TempDmozSite);
	}
	//------------------------------------------------------------------------
	/**
	 * ������������ ���� dmoz_topic � ��������� ���� ��������� � ���� ������
	 *
	 */
	private function SyncDmozTopic()
	{
		if ($this->DmozTopicCount > 0)
		{
			$string = "temp_dmoz_topics (topic_name, parent_name, rang) VALUES ";
			foreach ($this->TempDmozTopicArray as $temp)
			{
				$string = $string . "(" . $temp->GetSQL() . "), ";	
			}
			$string[strlen($string) - 2] = "\0";
			insertDataBase($string);
			$this->DmozTopicCount = 0;
		}	
		$this->TempDmozTopicArray = array();
	}
	//------------------------------------------------------------------------
	/**
	 * ������������ ���� dmoz_sites � ��������� ���� ��������� � ���� ������
	 *
	 */
	private function SyncDmozSites()
	{
		unset($this->TempDmozSiteArray[0]);
		if ($this->DmozSitesCount > 0)
		{
			$string = "temp_dmoz_sites (topic_name, title, passage, url, rang, topic_resolv, expage_resolv) VALUES ";
			foreach ($this->TempDmozSiteArray as $row)
			{
				foreach ($row as $col) 
				{
					$string = $string . "(" . $col->GetSQL() . "), ";
					unset($col);
				}
				unset($row);
			}
			$string[strlen($string) - 2] = "\0";
			insertDataBase($string);
			$this->DmozSitesCount = 0;
		}
		$this->TempDmozSiteArray = array(array());
	}
	//------------------------------------------------------------------------
	/**
	* �������� ������ � ������� temp_dmoz_topics, ���������� ������� dmoz_topics
	*
	*/
	private function testTempDmozTopics()
	{
		$flag = true;
		$rang = 1;
		while ((mysql_num_rows($temp_dmoz_topics = selectData("DISTINCT topic_name, parent_name FROM temp_dmoz_topics WHERE rang=" . $rang . " ORDER BY topic_name")) != 0) && ($flag))
		{
			$flag = false;
				while ($temp_topic = mysql_fetch_object($temp_dmoz_topics))
				{
					// � ������� ������� �����, ���� ������ ������
					if ($rang == 1)
					{
						$flag = true;
						insertDataBase("dmoz_topics (topic_name, parent_id) VALUES ('" . mysql_real_escape_string($temp_topic->topic_name) . "', " . 0 . ")");
					}
					else
					{
						if ((mysql_num_rows($dmoz_topics = selectData("DISTINCT topic_id FROM dmoz_topics WHERE topic_name='" . mysql_real_escape_string($temp_topic->parent_name) . "'")) != 0))
						{
							$flag = true;
							$parent_topic = mysql_fetch_object($dmoz_topics);
							insertDataBase("dmoz_topics (topic_name, parent_id) VALUES ('" . mysql_real_escape_string($temp_topic->topic_name) . "', " . $parent_topic->topic_id . ")");
						}
						else
						{
							// ������� �� ����� ��������
							$this->LogFile->Write(sprintf(NO_PARENT . "\n", $temp_topic->topic_name));
						}
					}
				}
			$rang++;
		}
		// ���������� �� ����� - �� �������� �������
		if (mysql_num_rows($temp_dmoz_topics = selectData("DISTINCT topic_name, parent_name FROM temp_dmoz_topics WHERE rang>=" . $rang)) != 0)
		{
			$this->LogFile->Write(sprintf(INTEGRITY_ERROR . "\n", $rang - 1));
		}
		$this->MaxTopicRang = $rang - 1;
	}
	//------------------------------------------------------------------------
	/**
	* �������� ������ � ������� temp_dmoz_sites, ���������� ������� dmoz_sites
	*
	*/
	private function testTempDmozSites()
	{
		for ($i = 1; $i <= $this->MaxTopicRang; $i++)
		{
			if ((mysql_num_rows($temp_dmoz_sites = selectData("DISTINCT topic_name, title, passage, url, topic_resolv, expage_resolv 
																from temp_dmoz_sites where rang=" . $i. " ORDER BY topic_name, url"))) != 0)
			{
				while ($temp_site = mysql_fetch_object($temp_dmoz_sites))
				{
					// ����� �������
					if ((mysql_num_rows($dmoz_topics = selectData("DISTINCT topic_id from dmoz_topics where topic_name='" . mysql_real_escape_string($temp_site->topic_name) . "'"))) != 0)
					{
						$temp_topic = mysql_fetch_object($dmoz_topics);
						// ������ �� ����� ��������
						if ($temp_site->topic_resolv && !$temp_site->expage_resolv)
						{
							$this->LogFile->Write(sprintf(PAGE_NOT_DESCRIPT . "\n", $temp_site->url));
						}
						// ������ ����������� (����� ���������������)
						elseif (!$temp_site->topic_resolv && $temp_site->expage_resolv)
						{
							$this->LogFile->Write(sprintf(UNRESOLV_PAGE . "\n", $temp_site->url));
							continue;
						}
						insertDataBase("dmoz_sites (topic_id, title, passage, url) VALUES (" . $temp_topic->topic_id . ", '" . mysql_real_escape_string($temp_site->title) . "', '" . mysql_real_escape_string($temp_site->passage) . "', '" . mysql_real_escape_string($temp_site->url) . "')");
					}
					
				}
			}
		}
	}
	//------------------------------------------------------------------------
}
//--------------------------------------------------------------------