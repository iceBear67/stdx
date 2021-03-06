#include <stdx/big_int.h>
#include <stdx/string.h>

stdx::big_int::big_int()
	:m_symbol(stdx::big_int_symbol::zero)
	, m_data()
{}

stdx::big_int::big_int(uint8_t v)
	: m_symbol(stdx::big_int_symbol::positive)
	, m_data()
{
	if (v != 0)
	{
		m_data.push_back(v);
	}
	else
	{
		m_symbol = stdx::big_int_symbol::zero;
	}
}

stdx::big_int::big_int(int8_t v)
	:m_symbol((v > 0) ? stdx::big_int_symbol::positive : stdx::big_int_symbol::negative)
	, m_data()
{
	if (v != 0)
	{
		_RemoveSymbol(v);
		m_data.push_back(v);
	}
	else
	{
		m_symbol = stdx::big_int_symbol::zero;
	}
}

stdx::big_int::big_int(uint16_t v)
	:m_symbol(stdx::big_int_symbol::positive)
	, m_data()
{
	if (v != 0)
	{
		byte_t* p = (byte_t*)&v;
		for (size_t i = 0; i < sizeof(uint16_t); i++)
		{
			m_data.push_back(p[i]);
		}
	}
	else
	{
		m_symbol = stdx::big_int_symbol::zero;
	}
}

stdx::big_int::big_int(int16_t v)
	:m_symbol((v > 0) ? stdx::big_int_symbol::positive : stdx::big_int_symbol::negative)
	, m_data()
{
	if (v != 0)
	{
		_RemoveSymbol(v);
		byte_t* p = (byte_t*)&v;
		for (size_t i = 0; i < sizeof(int16_t); i++)
		{
			m_data.push_back(p[i]);
		}
	}
	else
	{
		m_symbol = stdx::big_int_symbol::zero;
	}
}

stdx::big_int::big_int(uint32_t v)
	:m_symbol(stdx::big_int_symbol::positive)
	, m_data()
{
	if (v != 0)
	{
		byte_t* p = (byte_t*)&v;
		for (size_t i = 0; i < sizeof(uint32_t); i++)
		{
			m_data.push_back(p[i]);
		}
	}
	else
	{
		m_symbol = stdx::big_int_symbol::zero;
	}
}

stdx::big_int::big_int(int32_t v)
	:m_symbol((v > 0) ? stdx::big_int_symbol::positive : stdx::big_int_symbol::negative)
	, m_data()
{
	if (v != 0)
	{
		_RemoveSymbol(v);
		byte_t* p = (byte_t*)&v;
		for (size_t i = 0; i < sizeof(int32_t); i++)
		{
			m_data.push_back(p[i]);
		}
	}
	else
	{
		m_symbol = stdx::big_int_symbol::zero;
	}
}

stdx::big_int::big_int(uint64_t v)
	:m_symbol(stdx::big_int_symbol::positive)
	, m_data()
{
	if (v != 0)
	{
		char* p = (char*)&v;
		for (size_t i = 0; i < sizeof(uint64_t); i++)
		{
			m_data.push_back(p[i]);
		}
	}
	else
	{
		m_symbol = stdx::big_int_symbol::zero;
	}
}

stdx::big_int::big_int(int64_t v)
	:m_symbol((v > 0) ? stdx::big_int_symbol::positive : stdx::big_int_symbol::negative)
	, m_data()
{
	if (v != 0)
	{
		_RemoveSymbol(v);
		byte_t* p = (byte_t*)&v;
		for (size_t i = 0; i < sizeof(int64_t); i++)
		{
			m_data.push_back(p[i]);
		}
	}
	else
	{
		m_symbol = stdx::big_int_symbol::zero;
	}
}

stdx::big_int::big_int(byte_t* buffer, const size_t& size)
	:m_symbol(stdx::big_int_symbol::zero)
	,m_data()
{
	for (size_t i = 0; i < size; i++)
	{
		m_data.push_back(buffer[i]);
	}
	uint8_t tmp = 0;
	if (_BitCompareWith((byte_t*)&tmp,sizeof(tmp)) == 0)
	{
		m_data.clear();
	}
	else
	{
		m_symbol = stdx::big_int_symbol::positive;
	}
}

stdx::big_int::big_int(const std::vector<byte_t>& data)
	:m_symbol(stdx::big_int_symbol::zero)
	,m_data(data)
{
	uint8_t tmp = 0;
	if (_BitCompareWith((byte_t*)&tmp, sizeof(tmp)) == 0)
	{
		m_data.clear();
	}
	else
	{
		m_symbol = stdx::big_int_symbol::positive;
	}
}

stdx::big_int::big_int(const big_int& other)
	:m_symbol(other.m_symbol)
	,m_data(other.m_data)
{}

stdx::big_int::big_int(big_int&& other) noexcept
	:m_symbol(other.m_symbol)
	,m_data(std::move(other.m_data))
{}

bool stdx::big_int::operator==(int8_t v) const
{
	if ((m_symbol == stdx::big_int_symbol::zero) && (v == 0))
	{
		return true;
	}
	if (m_symbol != ((v > 0) ? stdx::big_int_symbol::positive : stdx::big_int_symbol::negative))
	{
		return false;
	}
	_RemoveSymbol(v);
	if (m_data.size() == sizeof(int8_t))
	{
		return m_data.front() == v;
	}
	else
	{
		if (m_data.front() == v)
		{
			for (size_t i = 1, size = m_data.size(); i < size; i++)
			{
				if (m_data.at(i) != 0)
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}
}

bool stdx::big_int::operator==(int16_t v) const
{
	if ((m_symbol == stdx::big_int_symbol::zero) && (v == 0))
	{
		return true;
	}
	if (m_symbol != ((v > 0) ? stdx::big_int_symbol::positive : stdx::big_int_symbol::negative))
	{
		return false;
	}
	_RemoveSymbol(v);
	if (m_data.size() == sizeof(int16_t))
	{
		int16_t* p = (int16_t*)m_data.data();
		return *p == v;
	}
	else
	{
		byte_t* buf = (byte_t*)&v;
		return (_BitCompareWith(buf, sizeof(int16_t))==0);
	}
}

bool stdx::big_int::operator==(int32_t v) const
{
	if ((m_symbol == stdx::big_int_symbol::zero) && (v == 0))
	{
		return true;
	}
	if (m_symbol != ((v > 0) ? stdx::big_int_symbol::positive : stdx::big_int_symbol::negative))
	{
		return false;
	}
	_RemoveSymbol(v);
	if (m_data.size() == sizeof(int32_t))
	{
		int32_t* p = (int32_t*)m_data.data();
		return *p == v;
	}
	else
	{
		byte_t* buf = (byte_t*)&v;
		return (_BitCompareWith(buf, sizeof(int32_t)) == 0);
	}
}

bool stdx::big_int::operator==(int64_t v) const
{
	if ((m_symbol == stdx::big_int_symbol::zero) && (v == 0))
	{
		return true;
	}
	if (m_symbol != ((v > 0) ? stdx::big_int_symbol::positive : stdx::big_int_symbol::negative))
	{
		return false;
	}
	_RemoveSymbol(v);
	if (m_data.size() == sizeof(int64_t))
	{
		int64_t* p = (int64_t*)m_data.data();
		return *p == v;
	}
	else
	{
		byte_t* buf = (byte_t*)&v;
		return (_BitCompareWith(buf, sizeof(int64_t)) == 0);
	}
}

bool stdx::big_int::operator==(uint8_t v) const
{
	if (m_symbol == stdx::big_int_symbol::negative)
	{
		return false;
	}
	if ((m_symbol == stdx::big_int_symbol::zero) && (v == 0))
	{
		return true;
	}

	if (m_data.size() == sizeof(uint8_t))
	{
		return (uint8_t)m_data.front() == v;
	}
	else
	{
		if ((uint8_t)m_data.front() == v)
		{
			for (size_t i = 1, size = m_data.size(); i < size; i++)
			{
				if (m_data.at(i) != 0)
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}
}

bool stdx::big_int::operator==(uint16_t v) const
{
	if (m_symbol == stdx::big_int_symbol::negative)
	{
		return false;
	}
	if ((m_symbol == stdx::big_int_symbol::zero) && (v == 0))
	{
		return true;
	}
	if (m_data.size() == sizeof(uint16_t))
	{
		uint16_t* p = (uint16_t*)m_data.data();
		return *p == v;
	}
	else
	{
		byte_t* buf = (byte_t*)&v;
		return (_BitCompareWith(buf, sizeof(uint16_t)) == 0);
	}
}

bool stdx::big_int::operator==(uint32_t v) const
{
	if (m_symbol == stdx::big_int_symbol::negative)
	{
		return false;
	}
	if ((m_symbol == stdx::big_int_symbol::zero) && (v == 0))
	{
		return true;
	}
	if (m_data.size() == sizeof(uint16_t))
	{
		uint16_t* p = (uint16_t*)m_data.data();
		return *p == v;
	}
	else
	{
		byte_t* buf = (byte_t*)&v;
		return (_BitCompareWith(buf, sizeof(uint32_t)) == 0);
	}
}

bool stdx::big_int::operator==(uint64_t v) const
{
	if (m_symbol == stdx::big_int_symbol::negative)
	{
		return false;
	}
	if ((m_symbol == stdx::big_int_symbol::zero) && (v == 0))
	{
		return true;
	}
	if (m_data.size() == sizeof(uint16_t))
	{
		uint16_t* p = (uint16_t*)m_data.data();
		return *p == v;
	}
	else
	{
		byte_t* buf = (byte_t*)&v;
		return (_BitCompareWith(buf, sizeof(uint64_t)) == 0);
	}
}

bool stdx::big_int::operator==(const big_int& other) const
{
	if (m_symbol != other.m_symbol)
	{
		return false;
	}
	if (other.m_data.size() == m_data.size())
	{
		for (size_t i = 0, size = m_data.size(); i < size; i++)
		{
			if (m_data.at(i) != other.m_data.at(i))
			{
				return false;
			}
		}
		return true;
	}
	else if(m_data.size() > other.m_data.size())
	{
		for (size_t i = 0,size=m_data.size(),other_size=other.m_data.size(); i < size; i++)
		{
			if (i<(other_size-1))
			{
				if (m_data.at(i)!=other.m_data.at(i))
				{
					return false;
				}
			}
			else
			{
				if (m_data.at(i)!=0)
				{
					return false;
				}
			}
		}
		return true;
	}
	else
	{
		for (size_t i = 0, size = m_data.size(), other_size = other.m_data.size(); i < other_size; i++)
		{
			if (i < (size - 1))
			{
				if (m_data.at(i) != other.m_data.at(i))
				{
					return false;
				}
			}
			else
			{
				if (other.m_data.at(i) != 0)
				{
					return false;
				}
			}
		}
		return true;
	}
}

stdx::big_int& stdx::big_int::operator=(int8_t v)
{
	if (!m_data.empty())
	{
		m_data.clear();
	}
	if (v != 0)
	{
		if (v < 0)
		{
			m_symbol = stdx::big_int_symbol::negative;
			v = (-v);
		}
		else
		{
			m_symbol = stdx::big_int_symbol::positive;
		}
		m_data.push_back(v);
	}
	else
	{
		m_symbol = stdx::big_int_symbol::zero;
	}
	return *this;
}

stdx::big_int& stdx::big_int::operator=(int16_t v)
{
	if (!m_data.empty())
	{
		m_data.clear();
	}
	if (v < 0)
	{
		m_symbol = stdx::big_int_symbol::negative;
		v = (-v);
	}
	else
	{
		m_symbol = stdx::big_int_symbol::positive;
	}
	if (v != 0)
	{
		char* p = (char*)&v;
		for (size_t i = 0; i < sizeof(int16_t); i++)
		{
			m_data.push_back(p[i]);
		}
	}
	else
	{
		m_symbol = stdx::big_int_symbol::zero;
	}
	return *this;
}

stdx::big_int& stdx::big_int::operator=(int32_t v)
{
	if (!m_data.empty())
	{
		m_data.clear();
	}
	if (v < 0)
	{
		m_symbol = stdx::big_int_symbol::negative;
		v = (-v);
	}
	else
	{
		m_symbol = stdx::big_int_symbol::positive;
	}
	if (v != 0)
	{
		char* p = (char*)&v;
		for (size_t i = 0; i < sizeof(int32_t); i++)
		{
			m_data.push_back(p[i]);
		}
	}
	else
	{
		m_symbol = stdx::big_int_symbol::zero;
	}
	return *this;
}

stdx::big_int& stdx::big_int::operator=(int64_t v)
{
	if (!m_data.empty())
	{
		m_data.clear();
	}
	if (v < 0)
	{
		m_symbol = stdx::big_int_symbol::negative;
		v = (-v);
	}
	else
	{
		m_symbol = stdx::big_int_symbol::positive;
	}
	if (v != 0)
	{
		char* p = (char*)&v;
		for (size_t i = 0; i < sizeof(int64_t); i++)
		{
			m_data.push_back(p[i]);
		}
	}
	else
	{
		m_symbol = stdx::big_int_symbol::zero;
	}
	return *this;
}

stdx::big_int& stdx::big_int::operator=(uint8_t v)
{
	if (!m_data.empty())
	{
		m_data.clear();
	}
	if (v != 0)
	{
		m_symbol = stdx::big_int_symbol::positive;
		m_data.push_back(v);
	}
	else
	{
		m_symbol = stdx::big_int_symbol::zero;
	}
	return *this;
}

stdx::big_int& stdx::big_int::operator=(uint16_t v)
{
	if (!m_data.empty())
	{
		m_data.clear();
	}
	if (v < 0)
	{
		v = (-v);
	}
	if (v != 0)
	{
		m_symbol = stdx::big_int_symbol::positive;
		char* p = (char*)&v;
		for (size_t i = 0; i < sizeof(uint16_t); i++)
		{
			m_data.push_back(p[i]);
		}
	}
	else
	{
		m_symbol = stdx::big_int_symbol::zero;
	}
	return *this;
}

stdx::big_int& stdx::big_int::operator=(uint32_t v)
{
	if (!m_data.empty())
	{
		m_data.clear();
	}
	if (v != 0)
	{
		m_symbol = stdx::big_int_symbol::positive;
		char* p = (char*)&v;
		for (size_t i = 0; i < sizeof(uint32_t); i++)
		{
			m_data.push_back(p[i]);
		}
	}
	else
	{
		m_symbol = stdx::big_int_symbol::zero;
	}
	return *this;
}

stdx::big_int& stdx::big_int::operator=(uint64_t v)
{
	if (!m_data.empty())
	{
		m_data.clear();
	}
	if (v != 0)
	{
		m_symbol = stdx::big_int_symbol::positive;
		char* p = (char*)&v;
		for (size_t i = 0; i < sizeof(uint64_t); i++)
		{
			m_data.push_back(p[i]);
		}
	}
	else
	{
		m_symbol = stdx::big_int_symbol::zero;
	}
	return *this;
}

stdx::big_int& stdx::big_int::operator=(const stdx::big_int& other)
{
	m_symbol = other.m_symbol;
	m_data = other.m_data;
	return *this;
}

stdx::big_int& stdx::big_int::operator=(stdx::big_int&& other) noexcept
{
	m_symbol = other.m_symbol;
	m_data = std::move(other.m_data);
	return *this;
}

int stdx::big_int::_BitCompareWith(byte_t *buffer, const size_t& buffer_size) const
{
	size_t size = m_data.size();

	if ((size==0)&&(buffer_size==0))
	{
		return 0;
	}
	if ((size >0)&&(buffer_size==0))
	{
		return 1;
	}
	if ((size == 0) && (buffer_size > 0))
	{
		return -1;
	}

	if (size == buffer_size)
	{
		for (size_t i = size-1;true; i--)
		{
			if (m_data.at(i)>buffer[i])
			{
				//this > buffer
				return 1;
			}
			else if(m_data.at(i) <buffer[i])
			{
				//this < buffer
				return -1;
			}
			if (i==0)
			{
				break;
			}
		}
		//this == buffer
		return 0;
	}
	else if (size > buffer_size)
	{
		for (size_t i = size-1,tmp=buffer_size-1;true; i--)
		{
			if (i > tmp)
			{
				if (m_data.at(i)!=0)
				{
					//this > buffer
					return 1;
				}
			}
			else
			{
				if (m_data.at(i) > buffer[i])
				{
					//this > buffer
					return 1;
				}
				else if (m_data.at(i) < buffer[i])
				{
					//this < buffer
					return -1;
				}
			}
			if (i==0)
			{
				break;
			}
		}
		//this == buffer
		return 0;
	}
	else
	{
		for (size_t i = buffer_size-1,tmp=size-1; true; i--)
		{
			if (i > tmp)
			{
				if (buffer[i] !=0)
				{
					//this < buffer
					return -1;
				}
			}
			else
			{
				if (m_data.at(i) > buffer[i])
				{
					//this > buffer
					return 1;
				}
				else if (m_data.at(i) < buffer[i])
				{
					//this < buffer
					return -1;
				}
			}
			if (i == 0)
			{
				break;
			}
		}
		//this == buffer
		return 0;
	}
}

int stdx::big_int::_BitCompareWith(const std::vector<byte_t>& other) const
{
	size_t size = m_data.size(),other_size = other.size();

	if ((size == 0) && (other_size == 0))
	{
		return 0;
	}
	if ((size > 0) && (other_size == 0))
	{
		return 1;
	}
	if ((size == 0) && (other_size > 0))
	{
		return -1;
	}

	if (size==other_size)
	{
		for (size_t i = size-1;true; i--)
		{
			if (m_data.at(i) > other.at(i))
			{
				//this > other
				return 1;
			}
			else if (m_data.at(i) < other.at(i))
			{
				//this < other
				return -1;
			}
			if (i==0)
			{
				break;
			}
		}
		//this == other
		return 0;
	}
	else if(size > other_size)
	{
		for (size_t i = size - 1, tmp = other_size - 1; true; i--)
		{
			if (i > tmp)
			{
				if (m_data.at(i) != 0)
				{
					//this > other
					return 1;
				}
			}
			else
			{
				if (m_data.at(i) > other.at(i))
				{
					//this > other
					return 1;
				}
				else if (m_data.at(i) < other.at(i))
				{
					//this < other
					return -1;
				}
			}
			if (i == 0)
			{
				break;
			}
		}
		//this == other
		return 0;
	}
	else
	{
		for (size_t i = other_size - 1, tmp = size - 1; true; i--)
		{
			if (i > tmp)
			{
				if (other.at(i) != 0)
				{
					//this < other
					return -1;
				}
			}
			else
			{
				if (m_data.at(i) > other.at(i))
				{
					//this > other
					return 1;
				}
				else if (m_data.at(i) < other.at(i))
				{
					//this < other
					return -1;
				}
			}
			if (i == 0)
			{
				break;
			}
		}
		//this == other
		return 0;
	}
}

bool stdx::big_int::operator>(int8_t v) const
{
	if (v == 0)
	{
		if (m_symbol == stdx::big_int_symbol::negative || m_symbol == stdx::big_int_symbol::zero)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else if (v > 0)
	{
		if (m_symbol == stdx::big_int_symbol::negative || m_symbol == stdx::big_int_symbol::zero)
		{
			return false;
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::positive || m_symbol == stdx::big_int_symbol::zero)
		{
			return true;
		}
	}

	if (m_data.empty())
	{
		return false;
	}

	bool tmp = (m_symbol == stdx::big_int_symbol::negative) && (v < 0);
	_RemoveSymbol(v);
	size_t size = m_data.size();
	if (size==sizeof(int8_t))
	{
		if (m_data.front() > v)
		{
			return tmp ? false : true;
		}
	}
	else
	{
		if (tmp)
		{
			if (m_data.front() < v)
			{
				for (size_t i = 1; i < size; i++)
				{
					if (m_data.at(i) != 0)
					{
						return false;
					}
				}
			}
			return true;
		}
		else
		{
			if (m_data.front() > v)
			{
				for (size_t i = 1; i < size; i++)
				{
					if (m_data.at(i) != 0)
					{
						return true;
					}
				}
			}
			return false;
		}
	}
	return false;
}

bool stdx::big_int::operator>(int16_t v) const
{
	if (v == 0)
	{
		if (m_symbol == stdx::big_int_symbol::negative || m_symbol == stdx::big_int_symbol::zero)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else if (v > 0)
	{
		if (m_symbol == stdx::big_int_symbol::negative || m_symbol == stdx::big_int_symbol::zero)
		{
			return false;
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::positive || m_symbol == stdx::big_int_symbol::zero)
		{
			return true;
		}
	}


	if (m_data.empty())
	{
		return false;
	}

	bool tmp = (m_symbol == stdx::big_int_symbol::negative) && (v < 0);

	_RemoveSymbol(v);
	if (m_data.size() == sizeof(int16_t))
	{
		uint16_t* p = (uint16_t*)m_data.data();
		if (tmp)
		{
			return *p < (uint16_t)v;
		}
		return *p > (uint16_t)v;
	}
	else
	{
		byte_t* p = (byte_t*)&v;
		if (tmp)
		{
			return (_BitCompareWith(p, sizeof(int16_t)) == -1);
		}
		return (_BitCompareWith(p, sizeof(int16_t)) == 1);
	}
}

bool stdx::big_int::operator>(int32_t v) const
{
	if (v == 0)
	{
		if (m_symbol == stdx::big_int_symbol::negative || m_symbol == stdx::big_int_symbol::zero)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else if (v > 0)
	{
		if (m_symbol == stdx::big_int_symbol::negative || m_symbol == stdx::big_int_symbol::zero)
		{
			return false;
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::positive || m_symbol == stdx::big_int_symbol::zero)
		{
			return true;
		}
	}


	if (m_data.empty())
	{
		return false;
	}

	bool tmp = (m_symbol == stdx::big_int_symbol::negative) && (v < 0);

	_RemoveSymbol(v);
	if (m_data.size() == sizeof(int32_t))
	{
		uint32_t* p = (uint32_t*)m_data.data();
		if (tmp)
		{
			return *p < (uint32_t)v;
		}
		return *p > (uint32_t)v;
	}
	else
	{
		byte_t* p = (byte_t*)&v;
		if (tmp)
		{
			return (_BitCompareWith(p, sizeof(int32_t)) == -1);
		}
		return (_BitCompareWith(p, sizeof(int32_t)) == 1);
	}
}

bool stdx::big_int::operator>(int64_t v) const
{
	if (v == 0)
	{
		if (m_symbol == stdx::big_int_symbol::negative || m_symbol == stdx::big_int_symbol::zero)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else if (v > 0)
	{
		if (m_symbol == stdx::big_int_symbol::negative || m_symbol == stdx::big_int_symbol::zero)
		{
			return false;
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::positive || m_symbol == stdx::big_int_symbol::zero)
		{
			return true;
		}
	}


	if (m_data.empty())
	{
		return false;
	}

	bool tmp = (m_symbol == stdx::big_int_symbol::negative) && (v < 0);

	_RemoveSymbol(v);
	if (m_data.size() == sizeof(int64_t))
	{
		uint64_t* p = (uint64_t*)m_data.data();
		if (tmp)
		{
			return *p < (uint64_t)v;
		}
		return *p > (uint64_t)v;
	}
	else
	{
		byte_t* p = (byte_t*)&v;
		if (tmp)
		{
			return (_BitCompareWith(p, sizeof(int64_t)) == -1);
		}
		return (_BitCompareWith(p, sizeof(int64_t)) == 1);
	}
}

bool stdx::big_int::operator>(uint8_t v) const
{
	if (v == 0)
	{
		if (m_symbol == stdx::big_int_symbol::negative || m_symbol == stdx::big_int_symbol::zero)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::negative || m_symbol == stdx::big_int_symbol::zero)
		{
			return false;
		}
	}

	if (m_data.empty())
	{
		return false;
	}

	bool tmp = (m_symbol == stdx::big_int_symbol::negative) && (v < 0);

	size_t size = m_data.size();
	if (((uint8_t)m_data.front()) > v)
	{
		return tmp ? false : true;
	}
	else if ((byte_t)m_data.front() == (byte_t)v)
	{
		return false;
	}
	else
	{
		if (size == 1)
		{
			return tmp ? true : false;
		}
		for (size_t i = 1; i < size; i++)
		{
			if (m_data.at(i) != 0)
			{
				return tmp ? false : true;
			}
		}
		return tmp ? true : false;
	}
}

bool stdx::big_int::operator>(uint16_t v) const
{
	if (v == 0)
	{
		if (m_symbol == stdx::big_int_symbol::negative || m_symbol == stdx::big_int_symbol::zero)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::negative || m_symbol == stdx::big_int_symbol::zero)
		{
			return false;
		}
	}

	if (m_data.empty())
	{
		return false;
	}

	if (m_data.size() == sizeof(uint16_t))
	{
		uint16_t* p = (uint16_t*)m_data.data();
		return *p > v;
	}
	else
	{
		byte_t* p = (byte_t*)&p;
		return (_BitCompareWith(p,sizeof(uint16_t))==1);
	}
}

bool stdx::big_int::operator>(uint32_t v) const
{
	if (v == 0)
	{
		if (m_symbol == stdx::big_int_symbol::negative || m_symbol == stdx::big_int_symbol::zero)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::negative || m_symbol == stdx::big_int_symbol::zero)
		{
			return false;
		}
	}

	if (m_data.empty())
	{
		return false;
	}

	if (m_data.size() == sizeof(uint32_t))
	{
		uint32_t* p = (uint32_t*)m_data.data();
		return *p > v;
	}
	else
	{
		byte_t* p = (byte_t*)&p;
		return (_BitCompareWith(p, sizeof(uint32_t)) == 1);
	}
}

bool stdx::big_int::operator>(uint64_t v) const
{
	if (v == 0)
	{
		if (m_symbol == stdx::big_int_symbol::negative || m_symbol == stdx::big_int_symbol::zero)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::negative || m_symbol == stdx::big_int_symbol::zero)
		{
			return false;
		}
	}

	if (m_data.empty())
	{
		return false;
	}

	if (m_data.size() == sizeof(uint64_t))
	{
		uint64_t* p = (uint64_t*)m_data.data();
		return *p > v;
	}
	else
	{
		byte_t* p = (byte_t*)&p;
		return (_BitCompareWith(p, sizeof(uint64_t)) == 1);
	}
}

bool stdx::big_int::operator>(const big_int& other)const
{
	if (m_symbol == stdx::big_int_symbol::zero)
	{
		if (other.m_symbol == stdx::big_int_symbol::zero)
		{
			return false;
		}
		if (other.m_symbol == stdx::big_int_symbol::positive)
		{
			return false;
		}
		if (other.m_symbol == stdx::big_int_symbol::negative)
		{
			return true;
		}
	}
	if (m_symbol == stdx::big_int_symbol::positive)
	{
		if ((other.m_symbol == stdx::big_int_symbol::zero) || (other.m_symbol == stdx::big_int_symbol::negative))
		{
			return true;
		}
	}
	if (m_symbol == stdx::big_int_symbol::negative)
	{
		if ((other.m_symbol == stdx::big_int_symbol::zero) || (other.m_symbol == stdx::big_int_symbol::positive))
		{
			return false;
		}
	}

	if (m_data.empty())
	{
		return false;
	}

	bool tmp = (m_symbol == stdx::big_int_symbol::negative) && (other.m_symbol == stdx::big_int_symbol::negative);
	if (tmp)
	{
		return (_BitCompareWith(other.m_data)==-1);
	}
	return (_BitCompareWith(other.m_data) == 1);
}

bool stdx::big_int::operator<(int8_t v) const
{
	if (v > 0)
	{
		if (m_symbol == stdx::big_int_symbol::negative || m_symbol == stdx::big_int_symbol::zero)
		{
			return true;
		}
	}
	else if (v == 0)
	{
		if (m_symbol == stdx::big_int_symbol::zero || m_symbol == stdx::big_int_symbol::positive)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::zero || m_symbol == stdx::big_int_symbol::positive)
		{
			return false;
		}
	}

	bool tmp = (v < 0) && (m_symbol == stdx::big_int_symbol::negative);

	_RemoveSymbol(v);
	if (m_data.size()==sizeof(int8_t))
	{
		if (m_data.front() < (byte_t)v)
		{
			return tmp?false:true;
		}
		else
		{
			return tmp ? true :false;
		}
	}
	else
	{
		if (tmp)
		{
			if (m_data.front() > (byte_t)v)
			{
				for (size_t i = 1, size = m_data.size(); i < size; i++)
				{
					if (m_data.at(i) != 0)
					{
						return true;
					}
				}
				return false;
			}
			else
			{
				return true;
			}
		}
		else
		{
			if (m_data.front() < (byte_t)v)
			{
				for (size_t i = 1, size = m_data.size(); i < size; i++)
				{
					if (m_data.at(i) != 0)
					{
						return false;
					}
				}
				return true;
			}
			else
			{
				return false;
			}
		}
	}
}

bool stdx::big_int::operator<(int16_t v) const
{
	if (v > 0)
	{
		if (m_symbol == stdx::big_int_symbol::negative || m_symbol == stdx::big_int_symbol::zero)
		{
			return true;
		}
	}
	else if (v == 0)
	{
		if (m_symbol == stdx::big_int_symbol::zero || m_symbol == stdx::big_int_symbol::positive)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::zero || m_symbol == stdx::big_int_symbol::positive)
		{
			return false;
		}
	}

	bool tmp = (v < 0) && (m_symbol == stdx::big_int_symbol::negative);
	
	_RemoveSymbol(v);
	byte_t *p = (byte_t*)&v;
	if (tmp)
	{
		return (_BitCompareWith(p,sizeof(int16_t))==1);
	}
	return (_BitCompareWith(p, sizeof(int16_t)) == -1);
}

bool stdx::big_int::operator<(int32_t v) const
{
	if (v>0)
	{
		if (m_symbol == stdx::big_int_symbol::negative || m_symbol == stdx::big_int_symbol::zero)
		{
			return true;
		}
	}
	else if(v ==0)
	{
		if (m_symbol == stdx::big_int_symbol::zero || m_symbol == stdx::big_int_symbol::positive)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::zero || m_symbol == stdx::big_int_symbol::positive)
		{
			return false;
		}
	}
	
	bool tmp = (v < 0) && (m_symbol == stdx::big_int_symbol::negative);

	_RemoveSymbol(v);
	byte_t* p = (byte_t*)&v;
	if (tmp)
	{
		return (_BitCompareWith(p, sizeof(int32_t)) == 1);
	}
	return (_BitCompareWith(p, sizeof(int32_t)) == -1);
}

bool stdx::big_int::operator<(int64_t v) const
{
	if (v > 0)
	{
		if (m_symbol == stdx::big_int_symbol::negative || m_symbol == stdx::big_int_symbol::zero)
		{
			return true;
		}
	}
	else if (v == 0)
	{
		if (m_symbol == stdx::big_int_symbol::zero || m_symbol == stdx::big_int_symbol::positive)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::zero || m_symbol == stdx::big_int_symbol::positive)
		{
			return false;
		}
	}

	bool tmp = (v < 0) && (m_symbol == stdx::big_int_symbol::negative);

	_RemoveSymbol(v);
	byte_t* p = (byte_t*)&v;
	if (tmp)
	{
		return (_BitCompareWith(p, sizeof(int64_t)) == 1);
	}
	return (_BitCompareWith(p, sizeof(int64_t)) == -1);
}

bool stdx::big_int::operator<(uint8_t v) const
{
	if (m_symbol == stdx::big_int_symbol::negative)
	{
		return true;
	}
	if (v==0)
	{
		if (m_symbol == stdx::big_int_symbol::positive || m_symbol == stdx::big_int_symbol::zero)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::zero || m_symbol == stdx::big_int_symbol::negative)
		{
			return true;
		}
	}

	if (m_data.size()==sizeof(uint8_t))
	{
		return (m_data.front() < v);
	}
	else
	{
		for (size_t i = 1,size=m_data.size(); i < size; i++)
		{
			if (m_data.at(i)!=0)
			{
				return false;
			}
		}
		return true;
	}
}

bool stdx::big_int::operator<(uint16_t v) const
{
	if (m_symbol == stdx::big_int_symbol::negative)
	{
		return true;
	}
	if (v == 0)
	{
		if (m_symbol == stdx::big_int_symbol::positive || m_symbol == stdx::big_int_symbol::zero)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::zero || m_symbol == stdx::big_int_symbol::negative)
		{
			return true;
		}
	}

	byte_t* p = (byte_t*)&v;
	return (_BitCompareWith(p, sizeof(uint16_t)) == -1);
}

bool stdx::big_int::operator<(uint32_t v) const
{
	if (m_symbol == stdx::big_int_symbol::negative)
	{
		return true;
	}
	if (v == 0)
	{
		if (m_symbol == stdx::big_int_symbol::positive || m_symbol == stdx::big_int_symbol::zero)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::zero || m_symbol == stdx::big_int_symbol::negative)
		{
			return true;
		}
	}

	byte_t* p = (byte_t*)&v;
	return (_BitCompareWith(p, sizeof(uint16_t)) == -1);
}

bool stdx::big_int::operator<(uint64_t v) const
{
	if (m_symbol == stdx::big_int_symbol::negative)
	{
		return true;
	}
	if (v == 0)
	{
		if (m_symbol == stdx::big_int_symbol::positive || m_symbol == stdx::big_int_symbol::zero)
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::zero || m_symbol == stdx::big_int_symbol::negative)
		{
			return true;
		}
	}

	byte_t* p = (byte_t*)&v;
	return (_BitCompareWith(p, sizeof(uint16_t)) == -1);
}

bool stdx::big_int::operator<(const big_int& other) const
{
	if (m_symbol == stdx::big_int_symbol::zero)
	{
		if (other.m_symbol == stdx::big_int_symbol::zero)
		{
			return false;
		}
		if (other.m_symbol == stdx::big_int_symbol::positive)
		{
			return true;
		}
		if (other.m_symbol == stdx::big_int_symbol::negative)
		{
			return false;
		}
	}
	if (m_symbol == stdx::big_int_symbol::positive)
	{
		if ((other.m_symbol == stdx::big_int_symbol::zero) || (other.m_symbol == stdx::big_int_symbol::negative))
		{
			return false;
		}
	}
	if (m_symbol == stdx::big_int_symbol::negative)
	{
		if ((other.m_symbol == stdx::big_int_symbol::zero) || (other.m_symbol == stdx::big_int_symbol::positive))
		{
			return true;
		}
	}

	if (m_data.empty())
	{
		return false;
	}

	bool tmp = (m_symbol == stdx::big_int_symbol::negative) && (other.m_symbol == stdx::big_int_symbol::negative);
	if (tmp)
	{
		return (_BitCompareWith(other.m_data) == 1);
	}
	return (_BitCompareWith(other.m_data) == -1);
}

stdx::uint16_union stdx::big_int::_BitAdd(byte_t a, byte_t b)
{
	uint16_union tmp;
	uint16_t t1 = a, t2 = b;
	tmp.value = t1 + t2;
	return tmp;
}

void stdx::big_int::_BitAdd(byte_t* buffer, const size_t& buffer_size)
{
	size_t size = m_data.size();
	if (size == buffer_size)
	{
		//保存进位
		byte_t tmp = 0;
		for (size_t i = 0; i < size; i++)
		{
			if (tmp!=0)
			{
				uint16_union r = _BitAdd(m_data.at(i),tmp);
				m_data.at(i) = r.low;
				//将高位保存到进位变量
				tmp = r.height;
				r = _BitAdd(m_data.at(i), buffer[i]);
				m_data.at(i) = r.low;
				tmp += r.height;
			}
			else
			{
				uint16_union r = _BitAdd(m_data.at(i), buffer[i]);
				tmp = r.height;
				m_data.at(i) = r.low;
			}
		}
		if (tmp!=0)
		{
			m_data.push_back(tmp);
		}
	}
	else if (size > buffer_size)
	{
		byte_t tmp = 0;
		for (size_t i = 0; i < buffer_size; i++)
		{
			if (tmp != 0)
			{
				uint16_union r = _BitAdd(m_data.at(i), tmp);
				m_data.at(i) = r.low;
				//将高位保存到进位变量
				tmp = r.height;
				r = _BitAdd(m_data.at(i), buffer[i]);
				m_data.at(i) = r.low;
				tmp += r.height;
			}
			else
			{
				uint16_union r = _BitAdd(m_data.at(i), buffer[i]);
				tmp = r.height;
				m_data.at(i) = r.low;
			}
		}

		for (size_t i = buffer_size;(tmp != 0)&&(i<size); i++)
		{
			uint16_union r = _BitAdd(m_data.at(i), tmp);
			m_data.at(i) = r.low;
			tmp = r.height;
		}
		if (tmp!=0)
		{
			m_data.push_back(tmp);
		}
	}
	else
	{
		byte_t tmp = 0;
		for (size_t i = 0; i < size; i++)
		{
			if (tmp != 0)
			{
				//进位
				uint16_union r = _BitAdd(m_data.at(i), tmp);
				m_data.at(i) = r.low;
				//将高位保存到进位变量
				tmp = r.height;
				r = _BitAdd(m_data.at(i), buffer[i]);
				m_data.at(i) = r.low;
				tmp += r.height;
			}
			else
			{
				uint16_union r = _BitAdd(m_data.at(i), buffer[i]);
				tmp = r.height;
				m_data.at(i) = r.low;
			}
		}
		for (size_t i = size; (tmp != 0) && (i < buffer_size); i++)
		{
			uint16_union r = _BitAdd(buffer[i], tmp);
			m_data.push_back(r.low);
			tmp = r.height;
		}
		if (tmp != 0)
		{
			m_data.push_back(tmp);
		}
	}
}

void stdx::big_int::_BitAdd(const std::vector<byte_t>& other)
{
	size_t size = m_data.size(),other_size = other.size();
	if (size == other_size)
	{
		//保存进位
		byte_t tmp = 0;
		for (size_t i = 0; i < size; i++)
		{
			if (tmp != 0)
			{
				uint16_union r = _BitAdd(m_data.at(i), tmp);
				m_data.at(i) = r.low;
				//将高位保存到进位变量
				tmp = r.height;
				r = _BitAdd(m_data.at(i), other.at(i));
				m_data.at(i) = r.low;
				tmp += r.height;
			}
			else
			{
				uint16_union r = _BitAdd(m_data.at(i), other.at(i));
				tmp = r.height;
				m_data.at(i) = r.low;
			}
		}
		if (tmp != 0)
		{
			m_data.push_back(tmp);
		}
	}
	else if (size > other_size)
	{
		byte_t tmp = 0;
		for (size_t i = 0; i < other_size; i++)
		{
			if (tmp != 0)
			{
				uint16_union r = _BitAdd(m_data.at(i), tmp);
				m_data.at(i) = r.low;
				//将高位保存到进位变量
				tmp = r.height;
				r = _BitAdd(m_data.at(i), other.at(i));
				m_data.at(i) = r.low;
				tmp += r.height;
			}
			else
			{
				uint16_union r = _BitAdd(m_data.at(i), other.at(i));
				tmp = r.height;
				m_data.at(i) = r.low;
			}
		}

		for (size_t i = other_size; (tmp != 0) && (i < size); i++)
		{
			uint16_union r = _BitAdd(m_data.at(i), tmp);
			m_data.at(i) = r.low;
			tmp = r.height;
		}
		if (tmp != 0)
		{
			m_data.push_back(tmp);
		}
	}
	else
	{
		byte_t tmp = 0;
		for (size_t i = 0; i < size; i++)
		{
			if (tmp != 0)
			{
				//进位
				uint16_union r = _BitAdd(m_data.at(i), tmp);
				m_data.at(i) = r.low;
				//将高位保存到进位变量
				tmp = r.height;
				r = _BitAdd(m_data.at(i), other.at(i));
				m_data.at(i) = r.low;
				tmp += r.height;
			}
			else
			{
				uint16_union r = _BitAdd(m_data.at(i), other.at(i));
				tmp = r.height;
				m_data.at(i) = r.low;
			}
		}
		for (size_t i = size; (tmp != 0) && (i < other_size); i++)
		{
			uint16_union r = _BitAdd(other.at(i), tmp);
			m_data.push_back(r.low);
			tmp = r.height;
		}
		if (tmp != 0)
		{
			m_data.push_back(tmp);
		}
	}
}

void stdx::big_int::_BitBack(byte_t* buffer, const size_t& buffer_size)
{
	uintptr_t offset = buffer_size - 1;
	_BitBack(buffer+offset, buffer, buffer_size - 1);
}

void stdx::big_int::_BitBack(byte_t* symbol, byte_t* buf, const size_t& buf_size)
{
	for (size_t i = 0; i < buf_size; i++)
	{
		buf[i] = ~buf[i];
	}
	if ((*symbol)&0x80)
	{
		*symbol = ~(*symbol);
		*symbol |= 0x80;
	}
	else
	{
		*symbol = ~(*symbol);
		*symbol ^= 0x80;
	}
}

void stdx::big_int::_BitBack(byte_t* symbol, std::vector<byte_t>& other)
{
	for (size_t i = 0,size=other.size(); i < size; i++)
	{
		other[i] = ~other[i];
	}
	if ((*symbol) & 0x80)
	{
		*symbol = ~(*symbol);
		*symbol |= 0x80;
	}
	else
	{
		*symbol = ~(*symbol);
		*symbol ^= 0x80;
	}
}

void stdx::big_int::_BitAddOne(byte_t* symbol, byte_t* buffer, const size_t& buffer_size)
{
	uint16_union tmp;
	tmp.value = 0;
	uint16_t a = buffer[0];
	tmp.value = a + 1;
	buffer[0] = tmp.low;
	if (tmp.height != 0)
	{
		for (size_t i = 1; i < buffer_size; i++)
		{
			if (tmp.height != 0)
			{
				uint16_t t = buffer[i];
				tmp.value = t + tmp.height;
				buffer[i] = tmp.low;
			}
		}
	}
	if (tmp.height != 0)
	{
		uint16_t t = *symbol;
		tmp.value = t + tmp.height;
		*symbol += tmp.low;
	}
}

void stdx::big_int::_BitAddOne(byte_t* symbol, std::vector<byte_t>& other)
{
	uint16_union tmp;
	tmp.value = 0;
	uint16_t a = other[0];
	tmp.value = a + 1;
	other[0] = tmp.low;
	if (tmp.height != 0)
	{
		for (size_t i = 1,size=other.size(); i < size; i++)
		{
			if (tmp.height != 0)
			{
				uint16_t t = other[i];
				tmp.value = t + tmp.height;
				other[i] = tmp.low;
			}
		}
	}
	if (tmp.height != 0)
	{
		uint16_t t = *symbol;
		tmp.value = t + tmp.height;
		*symbol += tmp.low;
	}
}

void stdx::big_int::_BitAddOne(byte_t* buffer, const size_t& buffer_size)
{
	_BitAddOne(buffer + (buffer_size - 1), buffer, buffer_size - 1);
}

void stdx::big_int::_ToComplement(byte_t* buffer, const size_t& buffer_size)
{
	_BitBack(buffer, buffer_size);
	_BitAddOne(buffer, buffer_size);
}

void stdx::big_int::_ToComplement(byte_t* symbol, byte_t* buffer, const size_t& buffer_size)
{
	_BitBack(symbol, buffer, buffer_size);
	_BitAddOne(symbol, buffer, buffer_size);
}

void stdx::big_int::_ToComplement(byte_t* symbol, std::vector<byte_t>& other)
{
	_BitBack(symbol, other);
	_BitAddOne(symbol, other);
}

void stdx::big_int::_ToTureForm(byte_t* buffer, const size_t& buffer_size)
{
	_BitBack(buffer, buffer_size);
	_BitAddOne(buffer, buffer_size);
}

void stdx::big_int::_ToTureForm(byte_t* symbol, byte_t* buffer, const size_t& buffer_size)
{
	_BitBack(symbol, buffer, buffer_size);
	_BitAddOne(symbol,buffer, buffer_size);
}

void stdx::big_int::_ToTureForm(byte_t* symbol, std::vector<byte_t>& other)
{
	_BitBack(symbol, other);
	_BitAddOne(symbol, other);
}

bool stdx::big_int::_BitSubstract(byte_t* buffer, const size_t& buffer_size)
{
	size_t size = m_data.size();
	byte_t buffer_symbol = 0x80, symbol = 0x00;
	if (buffer_size > size)
	{
		//补齐到buffer_size
		for (size_t i = 0,t=buffer_size-size; i < t; i++)
		{
			m_data.push_back(0x00);
		}
		//将buffer的数据转成补码
		_ToComplement(&buffer_symbol,buffer, buffer_size);
		//保存进位
		byte_t tmp = 0;
		//相加
		for (size_t i = 0; i < buffer_size; i++)
		{
			if (tmp != 0)
			{
				uint16_union r = _BitAdd(m_data.at(i), tmp);
				m_data.at(i) = r.low;
				//将高位保存到进位变量
				tmp = r.height;
				r = _BitAdd(m_data.at(i), buffer[i]);
				m_data.at(i) = r.low;
				tmp += r.height;
			}
			else
			{
				uint16_union r = _BitAdd(m_data.at(i), buffer[i]);
				tmp = r.height;
				m_data.at(i) = r.low;
			}
		}
		//符号位的运算
		uint16_t t1 = symbol,t2 = buffer_symbol,t3=tmp;
		stdx::uint16_union r;
		r.value = t1 + t2+t3;
		symbol = r.low;
		if (symbol & 0x80)
		{
			_ToTureForm(&symbol,m_data);
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (buffer_size < size)
	{
		//将buffer的数据转成补码
		_ToComplement(&buffer_symbol, buffer, buffer_size);
		byte_t pending = 0x00,buffer_end_byte = buffer_symbol;
		if (buffer_symbol & 0x80)
		{
			pending = 0xFF;
			buffer_end_byte ^= 0x80;
			buffer_symbol = 0x80;
		}
		//相加
		//保存进位
		byte_t tmp = 0;
		//相加
		for (size_t i = 0; i < buffer_size; i++)
		{
			if (tmp != 0)
			{
				uint16_union r = _BitAdd(m_data.at(i), tmp);
				m_data.at(i) = r.low;
				//将高位保存到进位变量
				tmp = r.height;
				r = _BitAdd(m_data.at(i), buffer[i]);
				m_data.at(i) = r.low;
				tmp += r.height;
			}
			else
			{
				uint16_union r = _BitAdd(m_data.at(i), buffer[i]);
				tmp = r.height;
				m_data.at(i) = r.low;
			}
		}
		for (size_t i = buffer_size; i < size; i++)
		{
			if (i == buffer_size)
			{
				if (tmp != 0)
				{
					uint16_union r = _BitAdd(m_data.at(i), tmp);
					m_data.at(i) = r.low;
					//将高位保存到进位变量
					tmp = r.height;
					r = _BitAdd(m_data.at(i), buffer_end_byte);
					m_data.at(i) = r.low;
					tmp += r.height;
				}
				else
				{
					uint16_union r = _BitAdd(m_data.at(i), buffer_end_byte);
					tmp = r.height;
					m_data.at(i) = r.low;
				}
			}
			else
			{
				if (tmp != 0)
				{
					uint16_union r = _BitAdd(m_data.at(i), tmp);
					m_data.at(i) = r.low;
					//将高位保存到进位变量
					tmp = r.height;
					r = _BitAdd(m_data.at(i), pending);
					m_data.at(i) = r.low;
					tmp += r.height;
				}
				else
				{
					uint16_union r = _BitAdd(m_data.at(i),pending);
					tmp = r.height;
					m_data.at(i) = r.low;
				}
			}
			//符号位的运算
			uint16_t t1 = symbol, t2 = buffer_symbol, t3 = tmp;
			stdx::uint16_union r;
			r.value = t1 + t2 + t3;
			symbol = r.low;
			if (symbol & 0x80)
			{
				_ToTureForm(&symbol, m_data);
				return true;
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		//将buffer的数据转成补码
		_ToComplement(&buffer_symbol, buffer, buffer_size);
		//保存进位
		byte_t tmp = 0;
		//相加
		for (size_t i = 0; i < size; i++)
		{
			if (tmp != 0)
			{
				uint16_union r = _BitAdd(m_data.at(i), tmp);
				m_data.at(i) = r.low;
				//将高位保存到进位变量
				tmp = r.height;
				r = _BitAdd(m_data.at(i), buffer[i]);
				m_data.at(i) = r.low;
				tmp += r.height;
			}
			else
			{
				uint16_union r = _BitAdd(m_data.at(i), buffer[i]);
				tmp = r.height;
				m_data.at(i) = r.low;
			}
		}
		//符号位的运算
		uint16_t t1 = symbol, t2 = buffer_symbol, t3 = tmp;
		stdx::uint16_union r;
		r.value = t1 + t2 + t3;
		symbol = r.low;
		if (symbol & 0x80)
		{
			_ToTureForm(&symbol, m_data);
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

bool stdx::big_int::_BitSubstract(const std::vector<byte_t>& other)
{
	std::vector<byte_t> _other = other;
	size_t size = m_data.size(), other_size=other.size();
	if (size > other_size)
	{
		for (size_t i = 0,count = size - other_size; i < count; i++)
		{
			_other.push_back(0x00);
		}
	}
	else if (size < other_size)
	{
		for (size_t i = 0,count =other_size-size; i < count; i++)
		{
			m_data.push_back(0x00);
		}
	}
	byte_t symbol=0x00, other_symbol=0x80;
	_ToComplement(&other_symbol,_other);
	//保存进位
	byte_t tmp = 0;
	//相加
	for (size_t i = 0; i < size; i++)
	{
		if (tmp != 0)
		{
			uint16_union r = _BitAdd(m_data.at(i), tmp);
			m_data.at(i) = r.low;
			//将高位保存到进位变量
			tmp = r.height;
			r = _BitAdd(m_data.at(i), _other[i]);
			m_data.at(i) = r.low;
			tmp += r.height;
		}
		else
		{
			uint16_union r = _BitAdd(m_data.at(i), _other[i]);
			tmp = r.height;
			m_data.at(i) = r.low;
		}
	}
	//符号位的运算
	uint16_t t1 = symbol, t2 = other_symbol, t3 = tmp;
	stdx::uint16_union r;
	r.value = t1 + t2 + t3;
	symbol = r.low;
	if (symbol & 0x80)
	{
		_ToTureForm(&symbol, m_data);
		return true;
	}
	else
	{
		return false;
	}
}

void stdx::big_int::operator+=(int8_t v)
{
	if (v == 0)
	{
		return;
	}
	if (v < 0)
	{
		if (this->operator==(0))
		{
			this->operator=(v);
			return;
		}
		else if (this->operator>(0))
		{
			v = -v;
			this->operator-=(v);
			return;
		}
	}
	if (v > 0)
	{
		if (this->operator==(0))
		{
			this->operator=(v);
			return;
		}
		else if (this->operator<(0))
		{
			v = -v;
			byte_t* p = (byte_t*)&v;
			_ToTureForm(p, sizeof(v));
			this->operator-=(v);
			return;
		}
	}
	_BitAdd((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator+=(int16_t v)
{
	if (v == 0)
	{
		return;
	}
	if (v < 0)
	{
		if (this->operator==(0))
		{
			this->operator=(v);
			return;
		}
		else if (this->operator>(0))
		{
			v = -v;
			this->operator-=(v);
			return;
		}
	}
	if (v > 0)
	{
		if (this->operator==(0))
		{
			this->operator=(v);
			return;
		}
		else if (this->operator<(0))
		{
			v = -v;
			byte_t* p = (byte_t*)&v;
			_ToTureForm(p, sizeof(v));
			this->operator-=(v);
			return;
		}
	}
	_BitAdd((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator+=(int32_t v)
{
	if (v == 0)
	{
		return;
	}
	if (v < 0)
	{
		if (this->operator==(0))
		{
			this->operator=(v);
			return;
		}
		else if (this->operator>(0))
		{
			v = -v;
			this->operator-=(v);
			return;
		}
	}
	if (v > 0)
	{
		if (this->operator==(0))
		{
			this->operator=(v);
			return;
		}
		else if (this->operator<(0))
		{
			v = -v;
			byte_t *p = (byte_t*)&v;
			_ToTureForm(p, sizeof(v));
			this->operator-=(v);
			return;
		}
	}
	_BitAdd((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator+=(int64_t v)
{
	if (v == 0)
	{
		return;
	}
	if (v < 0)
	{
		if (this->operator==(0))
		{
			this->operator=(v);
			return;
		}
		else if (this->operator>(0))
		{
			v = -v;
			this->operator-=(v);
			return;
		}
	}
	if (v > 0)
	{
		if (this->operator==(0))
		{
			this->operator=(v);
			return;
		}
		else if (this->operator<(0))
		{
			v = -v;
			byte_t* p = (byte_t*)&v;
			_ToTureForm(p, sizeof(v));
			this->operator-=(v);
			return;
		}
	}
	_BitAdd((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator+=(uint8_t v)
{
	if (v == 0)
	{
		return;
	}
	if (this->operator==(0))
	{
		this->operator=(v);
		return;
	}
	else if (this->operator<(0))
	{
		byte_t* p = (byte_t*)&v;
		bool ch_symbol = _BitSubstract(p, sizeof(v));
		uint8_t tmp = 0;
		if (ch_symbol)
		{
			if (m_symbol == stdx::big_int_symbol::negative)
			{
				m_symbol = stdx::big_int_symbol::positive;
			}
			else if (m_symbol == stdx::big_int_symbol::positive)
			{
				m_symbol = stdx::big_int_symbol::negative;
			}
		}
		else if (_BitCompareWith(&tmp, sizeof(uint8_t)) == 0)
		{
			m_symbol = stdx::big_int_symbol::zero;
			m_data.clear();
		}
		return;
	}
	_BitAdd((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator+=(uint16_t v)
{
	if (v == 0)
	{
		return;
	}
	if (this->operator==(0))
	{
		this->operator=(v);
		return;
	}
	else if (this->operator<(0))
	{
		byte_t* p = (byte_t*)&v;
		bool ch_symbol = _BitSubstract(p, sizeof(v));
		uint8_t tmp = 0;
		if (ch_symbol)
		{
			if (m_symbol == stdx::big_int_symbol::negative)
			{
				m_symbol = stdx::big_int_symbol::positive;
			}
			else if (m_symbol == stdx::big_int_symbol::positive)
			{
				m_symbol = stdx::big_int_symbol::negative;
			}
		}
		else if (_BitCompareWith(&tmp, sizeof(uint8_t)) == 0)
		{
			m_symbol = stdx::big_int_symbol::zero;
			m_data.clear();
		}
		return;
	}
	_BitAdd((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator+=(uint32_t v)
{
	if (v == 0)
	{
		return;
	}
	if (this->operator==(0))
	{
		this->operator=(v);
		return;
	}
	else if (this->operator<(0))
	{
		byte_t* p = (byte_t*)&v;
		bool ch_symbol = _BitSubstract(p, sizeof(v));
		uint8_t tmp = 0;
		if (ch_symbol)
		{
			if (m_symbol == stdx::big_int_symbol::negative)
			{
				m_symbol = stdx::big_int_symbol::positive;
			}
			else if (m_symbol == stdx::big_int_symbol::positive)
			{
				m_symbol = stdx::big_int_symbol::negative;
			}
		}
		else if (_BitCompareWith(&tmp, sizeof(uint8_t)) == 0)
		{
			m_symbol = stdx::big_int_symbol::zero;
			m_data.clear();
		}
		return;
	}
	_BitAdd((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator+=(uint64_t v)
{
	if (v == 0)
	{
		return;
	}
	if (this->operator==(0))
	{
		this->operator=(v);
		return;
	}
	else if (this->operator<(0))
	{
		byte_t* p = (byte_t*)&v;
		bool ch_symbol = _BitSubstract(p, sizeof(v));
		uint8_t tmp = 0;
		if (ch_symbol)
		{
			if (m_symbol == stdx::big_int_symbol::negative)
			{
				m_symbol = stdx::big_int_symbol::positive;
			}
			else if (m_symbol == stdx::big_int_symbol::positive)
			{
				m_symbol = stdx::big_int_symbol::negative;
			}
		}
		else if (_BitCompareWith(&tmp, sizeof(uint8_t)) == 0)
		{
			m_symbol = stdx::big_int_symbol::zero;
			m_data.clear();
		}
		return;
	}
	_BitAdd((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator+=(const big_int& other)
{
	if (other == 0)
	{
		return;
	}
	if (other < 0)
	{
		if (this->operator==(0))
		{
			m_symbol = other.m_symbol;
			m_data = other.m_data;
			return;
		}
		else if(this->operator>(0))
		{
			stdx::big_int tmp(other);
			tmp.m_symbol = stdx::big_int_symbol::positive;
			this->operator-=(tmp);
			return;
		}
	}
	if (other > 0)
	{
		
		if (this->operator==(0))
		{
			m_symbol = other.m_symbol;
			m_data = other.m_data;
			return;
		}
		else if (this->operator<(0))
		{
			stdx::big_int tmp(other);
			tmp.m_symbol = stdx::big_int_symbol::negative;
			this->operator-=(tmp);
			return;
		}
	}
	_BitAdd(other.m_data);
}

void stdx::big_int::operator-=(int8_t v)
{
	if (v == 0)
	{
		return;
	}
	if (v < 0)
	{
		if (this->operator==(0))
		{
			this->operator=(v);
			m_symbol = stdx::big_int_symbol::positive;
			return;
		}
		else if (this->operator>(0))
		{
			this->operator+=(-v);
			return;
		}
	}
	if (v > 0)
	{
		if (this->operator==(0))
		{
			this->operator=(v);
			m_symbol = stdx::big_int_symbol::negative;
			return;
		}
		else if (this->operator<(0))
		{
			this->operator+=(-v);
			return;
		}
	}
	byte_t* p = (byte_t*)&v;
	if (*(p + sizeof(v) - 1) & 0x80)
	{
		*(p + sizeof(v) - 1) ^= 0x80;
	}
	bool ch_symbol = _BitSubstract(p, sizeof(v));
	uint8_t tmp = 0;
	if (ch_symbol)
	{
		if (m_symbol == stdx::big_int_symbol::negative)
		{
			m_symbol = stdx::big_int_symbol::positive;
		}
		else if (m_symbol == stdx::big_int_symbol::positive)
		{
			m_symbol = stdx::big_int_symbol::negative;
		}
	}
	else if (_BitCompareWith(&tmp, sizeof(uint8_t)) == 0)
	{
		m_symbol = stdx::big_int_symbol::zero;
		m_data.clear();
	}
}

void stdx::big_int::operator-=(int16_t v)
{
	if (v == 0)
	{
		return;
	}
	if (v < 0)
	{
		if (this->operator==(0))
		{
			this->operator=(v);
			m_symbol = stdx::big_int_symbol::positive;
			return;
		}
		else if (this->operator>(0))
		{
			this->operator+=(-v);
			return;
		}
	}
	if (v > 0)
	{
		if (this->operator==(0))
		{
			this->operator=(v);
			m_symbol = stdx::big_int_symbol::negative;
			return;
		}
		else if (this->operator<(0))
		{
			this->operator+=(-v);
			return;
		}
	}
	byte_t* p = (byte_t*)&v;
	if (*(p + sizeof(v) - 1) & 0x80)
	{
		*(p + sizeof(v) - 1) ^= 0x80;
	}
	bool ch_symbol = _BitSubstract(p, sizeof(v));
	uint8_t tmp = 0;
	if (ch_symbol)
	{
		if (m_symbol == stdx::big_int_symbol::negative)
		{
			m_symbol = stdx::big_int_symbol::positive;
		}
		else if (m_symbol == stdx::big_int_symbol::positive)
		{
			m_symbol = stdx::big_int_symbol::negative;
		}
	}
	else if (_BitCompareWith(&tmp, sizeof(uint8_t)) == 0)
	{
		m_symbol = stdx::big_int_symbol::zero;
		m_data.clear();
	}
}

void stdx::big_int::operator-=(int32_t v)
{
	if (v == 0)
	{
		return;
	}
	if (v < 0)
	{
		if (this->operator==(0))
		{
			this->operator=(v);
			m_symbol = stdx::big_int_symbol::positive;
			return;
		}
		else if (this->operator>(0))
		{
			this->operator+=(-v);
			return;
		}
	}
	if (v > 0)
	{
		if (this->operator==(0))
		{
			this->operator=(v);
			m_symbol = stdx::big_int_symbol::negative;
			return;
		}
		else if (this->operator<(0))
		{
			this->operator+=(-v);
			return;
		}
	}
	byte_t* p = (byte_t*)&v;
	if (*(p+sizeof(v)-1)&0x80)
	{
		*(p + sizeof(v) - 1) ^=  0x80;
	}
	bool ch_symbol = _BitSubstract(p, sizeof(v));
	uint8_t tmp = 0;
	if (ch_symbol)
	{
		if (m_symbol == stdx::big_int_symbol::negative)
		{
			m_symbol = stdx::big_int_symbol::positive;
		}
		else if (m_symbol == stdx::big_int_symbol::positive)
		{
			m_symbol = stdx::big_int_symbol::negative;
		}
	}
	else if (_BitCompareWith(&tmp, sizeof(uint8_t)) == 0)
	{
		m_symbol = stdx::big_int_symbol::zero;
		m_data.clear();
	}
}

void stdx::big_int::operator-=(int64_t v)
{
	if (v == 0)
	{
		return;
	}
	if (v < 0)
	{
		if (this->operator==(0))
		{
			this->operator=(v);
			m_symbol = stdx::big_int_symbol::positive;
			return;
		}
		else if (this->operator>(0))
		{
			this->operator+=(-v);
			return;
		}
	}
	if (v > 0)
	{
		if (this->operator==(0))
		{
			this->operator=(v);
			m_symbol = stdx::big_int_symbol::negative;
			return;
		}
		else if (this->operator<(0))
		{
			this->operator+=(-v);
			return;
		}
	}
	byte_t* p = (byte_t*)&v;
	if (*(p + sizeof(v) - 1) & 0x80)
	{
		*(p + sizeof(v) - 1) ^= 0x80;
	}
	bool ch_symbol = _BitSubstract(p, sizeof(v));
	uint8_t tmp = 0;
	if (ch_symbol)
	{
		if (m_symbol == stdx::big_int_symbol::negative)
		{
			m_symbol = stdx::big_int_symbol::positive;
		}
		else if (m_symbol == stdx::big_int_symbol::positive)
		{
			m_symbol = stdx::big_int_symbol::negative;
		}
	}
	else if (_BitCompareWith(&tmp, sizeof(uint8_t)) == 0)
	{
		m_symbol = stdx::big_int_symbol::zero;
		m_data.clear();
	}
}

void stdx::big_int::operator-=(uint8_t v)
{
	if (v == 0)
	{
		return;
	}
	if (this->operator==(0))
	{
		this->operator=(v);
		m_symbol = stdx::big_int_symbol::negative;
		return;
	}
	else if (this->operator<(0))
	{
		_BitAdd((byte_t*)&v, sizeof(v));
		return;
	}
	bool ch_symbol = _BitSubstract((byte_t*)&v, sizeof(v));
	uint8_t tmp = 0;
	if (ch_symbol)
	{
		if (m_symbol == stdx::big_int_symbol::negative)
		{
			m_symbol = stdx::big_int_symbol::positive;
		}
		else if (m_symbol == stdx::big_int_symbol::positive)
		{
			m_symbol = stdx::big_int_symbol::negative;
		}
	}
	else if (_BitCompareWith(&tmp, sizeof(uint8_t)) == 0)
	{
		m_symbol = stdx::big_int_symbol::zero;
		m_data.clear();
	}
}

void stdx::big_int::operator-=(uint16_t v)
{
	if (v == 0)
	{
		return;
	}
	if (this->operator==(0))
	{
		this->operator=(v);
		m_symbol = stdx::big_int_symbol::negative;
		return;
	}
	else if (this->operator<(0))
	{
		_BitAdd((byte_t*)&v, sizeof(v));
		return;
	}
	bool ch_symbol = _BitSubstract((byte_t*)&v, sizeof(v));
	uint8_t tmp = 0;
	if (ch_symbol)
	{
		if (m_symbol == stdx::big_int_symbol::negative)
		{
			m_symbol = stdx::big_int_symbol::positive;
		}
		else if (m_symbol == stdx::big_int_symbol::positive)
		{
			m_symbol = stdx::big_int_symbol::negative;
		}
	}
	else if (_BitCompareWith(&tmp, sizeof(uint8_t)) == 0)
	{
		m_symbol = stdx::big_int_symbol::zero;
		m_data.clear();
	}
}

void stdx::big_int::operator-=(uint32_t v)
{
	if (v == 0)
	{
		return;
	}
	if (this->operator==(0))
	{
		this->operator=(v);
		m_symbol = stdx::big_int_symbol::negative;
		return;
	}
	else if (this->operator<(0))
	{
		_BitAdd((byte_t*)&v, sizeof(v));
		return;
	}
	bool ch_symbol = _BitSubstract((byte_t*)&v, sizeof(v));
	uint8_t tmp = 0;
	if (ch_symbol)
	{
		if (m_symbol == stdx::big_int_symbol::negative)
		{
			m_symbol = stdx::big_int_symbol::positive;
		}
		else if (m_symbol == stdx::big_int_symbol::positive)
		{
			m_symbol = stdx::big_int_symbol::negative;
		}
	}
	else if (_BitCompareWith(&tmp, sizeof(uint8_t)) == 0)
	{
		m_symbol = stdx::big_int_symbol::zero;
		m_data.clear();
	}
}

void stdx::big_int::operator-=(uint64_t v)
{
	if (v == 0)
	{
		return;
	}
	if (this->operator==(0))
	{
		this->operator=(v);
		m_symbol = stdx::big_int_symbol::negative;
		return;
	}
	else if (this->operator<(0))
	{
		_BitAdd((byte_t*)&v, sizeof(v));
		return;
	}
	bool ch_symbol = _BitSubstract((byte_t*)&v, sizeof(v));
	uint8_t tmp = 0;
	if (ch_symbol)
	{
		if (m_symbol == stdx::big_int_symbol::negative)
		{
			m_symbol = stdx::big_int_symbol::positive;
		}
		else if (m_symbol == stdx::big_int_symbol::positive)
		{
			m_symbol = stdx::big_int_symbol::negative;
		}
	}
	else if (_BitCompareWith(&tmp, sizeof(uint8_t)) == 0)
	{
		m_symbol = stdx::big_int_symbol::zero;
		m_data.clear();
	}
}

void stdx::big_int::operator-=(const big_int& other)
{
	if (other == 0)
	{
		return;
	}
	if (other < 0)
	{
		if (this->operator==(0))
		{
			this->operator=(other);
			m_symbol = stdx::big_int_symbol::positive;
			return;
		}
		else if (this->operator>(0))
		{
			stdx::big_int tmp(other);
			tmp.m_symbol = stdx::big_int_symbol::positive;
			this->operator+=(tmp);
			return;
		}
	}
	if (other > 0)
	{
		if (this->operator==(0))
		{
			this->operator=(other);
			m_symbol =stdx::big_int_symbol::negative;
			return;
		}
		else if (this->operator<(0))
		{
			stdx::big_int tmp(other);
			tmp.m_symbol = stdx::big_int_symbol::negative;
			this->operator+=(tmp);
			return;
		}
	}
	bool ch_symbol = _BitSubstract(other.m_data);
	uint8_t tmp = 0;
	if (ch_symbol)
	{
		if (m_symbol == stdx::big_int_symbol::negative)
		{
			m_symbol = stdx::big_int_symbol::positive;
		}
		else if (m_symbol == stdx::big_int_symbol::positive)
		{
			m_symbol = stdx::big_int_symbol::negative;
		}
	}
	else if (_BitCompareWith(&tmp, sizeof(uint8_t)) == 0)
	{
		m_symbol = stdx::big_int_symbol::zero;
		m_data.clear();
	}
}

void stdx::big_int::operator*=(int8_t v)
{
	if (v == 0)
	{
		this->operator=(0);
		return;
	}
	if (this->operator==(0))
	{
		return;
	}
	stdx::big_int t1(*this);
	if (v<0)
	{
		if (m_symbol == stdx::big_int_symbol::positive)
		{
			m_symbol = stdx::big_int_symbol::negative;
			for (int8_t i(v); i < -1; ++i)
			{
				this->operator+=(t1);
			}
		}
		else if (m_symbol == stdx::big_int_symbol::negative)
		{
			m_symbol = stdx::big_int_symbol::positive;
			for (int8_t i(v); i < -1; ++i)
			{
				this->operator-=(t1);
			}
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::positive)
		{
			for (int8_t i(1); i < v; ++i)
			{
				this->operator+=(t1);
			}
		}
		else if (m_symbol == stdx::big_int_symbol::negative)
		{
			for (int8_t i(1); i < v; ++i)
			{
				this->operator-=(t1);
			}
		}
	}
}

void stdx::big_int::operator*=(int16_t v)
{
	if (v == 0)
	{
		this->operator=(0);
		return;
	}
	if (this->operator==(0))
	{
		return;
	}
	stdx::big_int t1(*this);
	if (v < 0)
	{
		if (m_symbol == stdx::big_int_symbol::positive)
		{
			m_symbol = stdx::big_int_symbol::negative;
			for (int16_t i(v); i < -1; ++i)
			{
				this->operator+=(t1);
			}
		}
		else if (m_symbol == stdx::big_int_symbol::negative)
		{
			m_symbol = stdx::big_int_symbol::positive;
			for (int16_t i(v); i < -1; ++i)
			{
				this->operator-=(t1);
			}
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::positive)
		{
			for (int16_t i(1); i < v; ++i)
			{
				this->operator+=(t1);
			}
		}
		else if (m_symbol == stdx::big_int_symbol::negative)
		{
			for (int16_t i(1); i < v; ++i)
			{
				this->operator-=(t1);
			}
		}
	}
}

void stdx::big_int::operator*=(int32_t v)
{
	if (v == 0)
	{
		this->operator=(0);
		return;
	}
	if (this->operator==(0))
	{
		return;
	}
	stdx::big_int t1(*this);
	if (v < 0)
	{
		if (m_symbol == stdx::big_int_symbol::positive)
		{
			m_symbol = stdx::big_int_symbol::negative;
			for (int32_t i(v); i < -1; ++i)
			{
				this->operator+=(t1);
			}
		}
		else if (m_symbol == stdx::big_int_symbol::negative)
		{
			m_symbol = stdx::big_int_symbol::positive;
			for (int32_t i(v); i < -1; ++i)
			{
				this->operator-=(t1);
			}
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::positive)
		{
			for (int32_t i(1); i < v; ++i)
			{
				this->operator+=(t1);
			}
		}
		else if (m_symbol == stdx::big_int_symbol::negative)
		{
			for (int32_t i(1); i < v; ++i)
			{
				this->operator-=(t1);
			}
		}
	}
}

void stdx::big_int::operator*=(int64_t v)
{
	if (v == 0)
	{
		this->operator=(0);
		return;
	}
	if (this->operator==(0))
	{
		return;
	}
	stdx::big_int t1(*this);
	if (v < 0)
	{
		if (m_symbol == stdx::big_int_symbol::positive)
		{
			m_symbol = stdx::big_int_symbol::negative;
			for (int64_t i(v); i < -1; ++i)
			{
				this->operator+=(t1);
			}
		}
		else if (m_symbol == stdx::big_int_symbol::negative)
		{
			m_symbol = stdx::big_int_symbol::positive;
			for (int64_t i(v); i < -1; ++i)
			{
				this->operator-=(t1);
			}
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::positive)
		{
			for (int64_t i(1); i < v; ++i)
			{
				this->operator+=(t1);
			}
		}
		else if (m_symbol == stdx::big_int_symbol::negative)
		{
			for (int64_t i(1); i < v; ++i)
			{
				this->operator-=(t1);
			}
		}
	}
}

void stdx::big_int::operator*=(uint8_t v)
{
	if (v == 0)
	{
		this->operator=(0);
		return;
	}
	if (this->operator==(0))
	{
		return;
	}
	stdx::big_int t1(*this);
	if (m_symbol == stdx::big_int_symbol::positive)
	{
		for (uint8_t i(1); i < v; ++i)
		{
			this->operator+=(t1);
		}
	}
	else if (m_symbol == stdx::big_int_symbol::negative)
	{
		for (uint8_t i(1); i < v; ++i)
		{
			this->operator-=(t1);
		}
	}
}

void stdx::big_int::operator*=(uint16_t v)
{
	if (v == 0)
	{
		this->operator=(0);
		return;
	}
	if (this->operator==(0))
	{
		return;
	}
	stdx::big_int t1(*this);
	if (m_symbol == stdx::big_int_symbol::positive)
	{
		for (uint16_t i(1); i < v; ++i)
		{
			this->operator+=(t1);
		}
	}
	else if (m_symbol == stdx::big_int_symbol::negative)
	{
		for (uint16_t i(1); i < v; ++i)
		{
			this->operator-=(t1);
		}
	}
}

void stdx::big_int::operator*=(uint32_t v)
{
	if (v == 0)
	{
		this->operator=(0);
		return;
	}
	if (this->operator==(0))
	{
		return;
	}
	stdx::big_int t1(*this);
	if (m_symbol == stdx::big_int_symbol::positive)
	{
		for (uint32_t i(1); i < v; ++i)
		{
			this->operator+=(t1);
		}
	}
	else if (m_symbol == stdx::big_int_symbol::negative)
	{
		for (uint32_t i(1); i < v; ++i)
		{
			this->operator-=(t1);
		}
	}
}

void stdx::big_int::operator*=(uint64_t v)
{
	if (v == 0)
	{
		this->operator=(0);
		return;
	}
	if (this->operator==(0))
	{
		return;
	}
	stdx::big_int t1(*this);
	if (m_symbol == stdx::big_int_symbol::positive)
	{
		for (uint64_t i(1); i < v; ++i)
		{
			this->operator+=(t1);
		}
	}
	else if (m_symbol == stdx::big_int_symbol::negative)
	{
		for (uint64_t i(1); i < v; ++i)
		{
			this->operator-=(t1);
		}
	}
}

void stdx::big_int::operator*=(const stdx::big_int& other)
{
	if (other == 0)
	{
		this->operator=(0);
		return;
	}
	if (this->operator==(0))
	{
		return;
	}
	stdx::big_int t1(*this);
	if (other < 0)
	{
		if (m_symbol == stdx::big_int_symbol::positive)
		{
			m_symbol = stdx::big_int_symbol::negative;
			for (stdx::big_int i(other); i < -1; ++i)
			{
				this->operator+=(t1);
			}
		}
		else if (m_symbol == stdx::big_int_symbol::negative)
		{
			m_symbol = stdx::big_int_symbol::positive;
			for (stdx::big_int i(other); i < -1; ++i)
			{
				this->operator-=(t1);
			}
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::positive)
		{
			for (stdx::big_int i(1); i < other; ++i)
			{
				this->operator+=(t1);
			}
		}
		else if (m_symbol == stdx::big_int_symbol::negative)
		{
			for (stdx::big_int i(1); i < other; ++i)
			{
				this->operator-=(t1);
			}
		}
	}
}

void stdx::big_int::operator/=(int8_t v)
{
	if (v == 0)
	{
		throw std::domain_error("cann't divided by 0");
	}
	if (this->operator==(0))
	{
		return;
	}
	if (v == 1)
	{
		return;
	}
	if (v == -1)
	{
		m_symbol = (m_symbol == stdx::big_int_symbol::positive) ? stdx::big_int_symbol::negative : stdx::big_int_symbol::positive;
		return;
	}
	stdx::big_int tmp(*this);
	this->operator=(0);
	if (v<0)
	{
		if (tmp.m_symbol == stdx::big_int_symbol::positive)
		{
			while (tmp >= v)
			{
				tmp += v;
				this->operator+= (1);
			}
			m_symbol = stdx::big_int_symbol::negative;
		}
		else if (tmp.m_symbol == stdx::big_int_symbol::negative)
		{
			while (tmp <= v)
			{
				tmp -= v;
				this->operator+= (1);
			}
			m_symbol = stdx::big_int_symbol::positive;
		}
	}
	else
	{
		if (tmp.m_symbol == stdx::big_int_symbol::positive)
		{
			while (tmp >= v)
			{
				tmp -= v;
				this->operator+= (1);
			}
		}
		else if (tmp.m_symbol == stdx::big_int_symbol::negative)
		{
			while (tmp <= v)
			{
				tmp += v;
				this->operator+= (1);
			}
		}
	}
}

void stdx::big_int::operator/=(int16_t v)
{
	if (v == 0)
	{
		throw std::domain_error("cann't divided by 0");
	}
	if (this->operator==(0))
	{
		return;
	}
	if (v == 1)
	{
		return;
	}
	if (v == -1)
	{
		m_symbol = (m_symbol == stdx::big_int_symbol::positive) ? stdx::big_int_symbol::negative : stdx::big_int_symbol::positive;
		return;
	}
	stdx::big_int tmp(*this);
	this->operator=(0);
	if (v < 0)
	{
		if (tmp.m_symbol == stdx::big_int_symbol::positive)
		{
			while (tmp >= v)
			{
				tmp += v;
				this->operator+= (1);
			}
			m_symbol = stdx::big_int_symbol::negative;
		}
		else if (tmp.m_symbol == stdx::big_int_symbol::negative)
		{
			while (tmp <= v)
			{
				tmp -= v;
				this->operator+= (1);
			}
			m_symbol = stdx::big_int_symbol::positive;
		}
	}
	else
	{
		if (tmp.m_symbol == stdx::big_int_symbol::positive)
		{
			while (tmp >= v)
			{
				tmp -= v;
				this->operator+= (1);
			}
		}
		else if (tmp.m_symbol == stdx::big_int_symbol::negative)
		{
			while (tmp <= v)
			{
				tmp += v;
				this->operator+= (1);
			}
		}
	}
}

void stdx::big_int::operator/=(int32_t v)
{
	if (v == 0)
	{
		throw std::domain_error("cann't divided by 0");
	}
	if (this->operator==(0))
	{
		return;
	}
	if (v == 1)
	{
		return;
	}
	if (v == -1)
	{
		m_symbol = (m_symbol == stdx::big_int_symbol::positive) ? stdx::big_int_symbol::negative : stdx::big_int_symbol::positive;
		return;
	}
	stdx::big_int tmp(*this);
	this->operator=(0);
	if (v < 0)
	{
		if (tmp.m_symbol == stdx::big_int_symbol::positive)
		{
			while (tmp >= v)
			{
				tmp += v;
				this->operator+= (1);
			}
			m_symbol = stdx::big_int_symbol::negative;
		}
		else if (tmp.m_symbol == stdx::big_int_symbol::negative)
		{
			while (tmp <= v)
			{
				tmp -= v;
				this->operator+= (1);
			}
			m_symbol = stdx::big_int_symbol::positive;
		}
	}
	else
	{
		if (tmp.m_symbol == stdx::big_int_symbol::positive)
		{
			while (tmp >= v)
			{
				tmp -= v;
				this->operator+= (1);
			}
		}
		else if (tmp.m_symbol == stdx::big_int_symbol::negative)
		{
			while (tmp <= v)
			{
				tmp += v;
				this->operator+= (1);
			}
		}
	}
}

void stdx::big_int::operator/=(int64_t v)
{
	if (v == 0)
	{
		throw std::domain_error("cann't divided by 0");
	}
	if (this->operator==(0))
	{
		return;
	}
	if (v == 1)
	{
		return;
	}
	if (v == -1)
	{
		m_symbol = (m_symbol == stdx::big_int_symbol::positive) ? stdx::big_int_symbol::negative : stdx::big_int_symbol::positive;
		return;
	}
	stdx::big_int tmp(*this);
	this->operator=(0);
	if (v < 0)
	{
		if (tmp.m_symbol == stdx::big_int_symbol::positive)
		{
			while (tmp >= v)
			{
				tmp += v;
				this->operator+= (1);
			}
			m_symbol = stdx::big_int_symbol::negative;
		}
		else if (tmp.m_symbol == stdx::big_int_symbol::negative)
		{
			while (tmp <= v)
			{
				tmp -= v;
				this->operator+= (1);
			}
			m_symbol = stdx::big_int_symbol::positive;
		}
	}
	else
	{
		if (tmp.m_symbol == stdx::big_int_symbol::positive)
		{
			while (tmp >= v)
			{
				tmp -= v;
				this->operator+= (1);
			}
		}
		else if (tmp.m_symbol == stdx::big_int_symbol::negative)
		{
			while (tmp <= v)
			{
				tmp += v;
				this->operator+= (1);
			}
		}
	}
}

void stdx::big_int::operator/=(uint8_t v)
{
	if (v == 0)
	{
		throw std::domain_error("cann't divided by 0");
	}
	if (this->operator==(0))
	{
		return;
	}
	if (v == 1)
	{
		return;
	}
	stdx::big_int tmp(*this);
	this->operator=(0);
	if (tmp.m_symbol == stdx::big_int_symbol::positive)
	{
		while (tmp >= v)
		{
			tmp -= v;
			this->operator+= (1);
		}
	}
	else if (tmp.m_symbol == stdx::big_int_symbol::negative)
	{
		while (tmp <= v)
		{
			tmp += v;
			this->operator+= (1);
		}
	}
}

void stdx::big_int::operator/=(uint16_t v)
{
	if (v == 0)
	{
		throw std::domain_error("cann't divided by 0");
	}
	if (this->operator==(0))
	{
		return;
	}
	if (v == 1)
	{
		return;
	}
	stdx::big_int tmp(*this);
	this->operator=(0);
	if (tmp.m_symbol == stdx::big_int_symbol::positive)
	{
		while (tmp >= v)
		{
			tmp -= v;
			this->operator+= (1);
		}
	}
	else if (tmp.m_symbol == stdx::big_int_symbol::negative)
	{
		while (tmp <= v)
		{
			tmp += v;
			this->operator+= (1);
		}
	}
}

void stdx::big_int::operator/=(uint32_t v)
{
	if (v == 0)
	{
		throw std::domain_error("cann't divided by 0");
	}
	if (this->operator==(0))
	{
		return;
	}
	if (v == 1)
	{
		return;
	}
	stdx::big_int tmp(*this);
	this->operator=(0);
	if (tmp.m_symbol == stdx::big_int_symbol::positive)
	{
		while (tmp >= v)
		{
			tmp -= v;
			this->operator+= (1);
		}
	}
	else if (tmp.m_symbol == stdx::big_int_symbol::negative)
	{
		while (tmp <= v)
		{
			tmp += v;
			this->operator+= (1);
		}
	}
}

void stdx::big_int::operator/=(uint64_t v)
{
	if (v == 0)
	{
		throw std::domain_error("cann't divided by 0");
	}
	if (this->operator==(0))
	{
		return;
	}
	if (v == 1)
	{
		return;
	}
	stdx::big_int tmp(*this);
	this->operator=(0);
	if (tmp.m_symbol == stdx::big_int_symbol::positive)
	{
		while (tmp >= v)
		{
			tmp -= v;
			this->operator+= (1);
		}
	}
	else if (tmp.m_symbol == stdx::big_int_symbol::negative)
	{
		while (tmp <= v)
		{
			tmp += v;
			this->operator+= (1);
		}
	}
}

void stdx::big_int::operator/=(const stdx::big_int& other)
{
	if (other == 0)
	{
		throw std::domain_error("cann't divided by 0");
	}
	if (this->operator==(0))
	{
		return;
	}
	if (other == 1)
	{
		return;
	}
	if (other == -1)
	{
		m_symbol = (m_symbol == stdx::big_int_symbol::positive) ? stdx::big_int_symbol::negative : stdx::big_int_symbol::positive;
		return;
	}
	stdx::big_int tmp(*this);
	this->operator=(0);
	if (other < 0)
	{
		if (tmp.m_symbol == stdx::big_int_symbol::positive)
		{
			while (tmp >= other)
			{
				tmp += other;
				this->operator+= (1);
			}
			m_symbol = stdx::big_int_symbol::negative;
		}
		else if (tmp.m_symbol == stdx::big_int_symbol::negative)
		{
			while (tmp <= other)
			{
				tmp -= other;
				this->operator+= (1);
			}
			m_symbol = stdx::big_int_symbol::positive;
		}
	}
	else
	{
		if (tmp.m_symbol == stdx::big_int_symbol::positive)
		{
			while (tmp >= other)
			{
				tmp -= other;
				this->operator+= (1);
			}
		}
		else if (tmp.m_symbol == stdx::big_int_symbol::negative)
		{
			while (tmp <= other)
			{
				tmp += other;
				this->operator+= (1);
			}
		}
	}
}

void stdx::big_int::operator%=(int8_t v)
{
	if (v == 0)
	{
		throw std::domain_error("cann't divided by 0");
	}
	if (this->operator==(0))
	{
		return;
	}
	if (v == 1 || v == -1)
	{
		this->operator=(0);
		return;
	}
	if (v < 0)
	{
		if (m_symbol == stdx::big_int_symbol::positive)
		{
			while (this->operator>=(v))
			{
				this->operator+=(v);
			}
			m_symbol = stdx::big_int_symbol::negative;
		}
		else if (m_symbol == stdx::big_int_symbol::negative)
		{
			while (this->operator<=(v))
			{
				this->operator-=(v);
			}
			m_symbol = stdx::big_int_symbol::positive;
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::positive)
		{
			while (this->operator>=(v))
			{
				this->operator-=(v);
			}
		}
		else if (m_symbol == stdx::big_int_symbol::negative)
		{
			while (this->operator<=(v))
			{
				this->operator+=(v);
			}
		}
	}
}

void stdx::big_int::operator%=(int16_t v)
{
	if (v == 0)
	{
		throw std::domain_error("cann't divided by 0");
	}
	if (this->operator==(0))
	{
		return;
	}
	if (v == 1 || v == -1)
	{
		this->operator=(0);
		return;
	}
	if (v < 0)
	{
		if (m_symbol == stdx::big_int_symbol::positive)
		{
			while (this->operator>=(v))
			{
				this->operator+=(v);
			}
			m_symbol = stdx::big_int_symbol::negative;
		}
		else if (m_symbol == stdx::big_int_symbol::negative)
		{
			while (this->operator<=(v))
			{
				this->operator-=(v);
			}
			m_symbol = stdx::big_int_symbol::positive;
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::positive)
		{
			while (this->operator>=(v))
			{
				this->operator-=(v);
			}
		}
		else if (m_symbol == stdx::big_int_symbol::negative)
		{
			while (this->operator<=(v))
			{
				this->operator+=(v);
			}
		}
	}
}

void stdx::big_int::operator%=(int32_t v)
{
	if (v == 0)
	{
		throw std::domain_error("cann't divided by 0");
	}
	if (this->operator==(0))
	{
		return;
	}
	if (v == 1 || v == -1)
	{
		this->operator=(0);
		return;
	}
	if (v < 0)
	{
		if (m_symbol == stdx::big_int_symbol::positive)
		{
			while (this->operator>=(v))
			{
				this->operator+=(v);
			}
			m_symbol = stdx::big_int_symbol::negative;
		}
		else if (m_symbol == stdx::big_int_symbol::negative)
		{
			while (this->operator<=(v))
			{
				this->operator-=(v);
			}
			m_symbol = stdx::big_int_symbol::positive;
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::positive)
		{
			while (this->operator>=(v))
			{
				this->operator-=(v);
			}
		}
		else if (m_symbol == stdx::big_int_symbol::negative)
		{
			while (this->operator<=(v))
			{
				this->operator+=(v);
			}
		}
	}
}

void stdx::big_int::operator%=(int64_t v)
{
	if (v == 0)
	{
		throw std::domain_error("cann't divided by 0");
	}
	if (this->operator==(0))
	{
		return;
	}
	if (v == 1 || v == -1)
	{
		this->operator=(0);
		return;
	}
	if (v < 0)
	{
		if (m_symbol == stdx::big_int_symbol::positive)
		{
			while (this->operator>=(v))
			{
				this->operator+=(v);
			}
			m_symbol = stdx::big_int_symbol::negative;
		}
		else if (m_symbol == stdx::big_int_symbol::negative)
		{
			while (this->operator<=(v))
			{
				this->operator-=(v);
			}
			m_symbol = stdx::big_int_symbol::positive;
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::positive)
		{
			while (this->operator>=(v))
			{
				this->operator-=(v);
			}
		}
		else if (m_symbol == stdx::big_int_symbol::negative)
		{
			while (this->operator<=(v))
			{
				this->operator+=(v);
			}
		}
	}
}

void stdx::big_int::operator%=(uint8_t v)
{
	if (v == 0)
	{
		throw std::domain_error("cann't divided by 0");
	}
	if (v == 1)
	{
		this->operator=(0);
		return;
	}
	if (this->operator==(0))
	{
		return;
	}
	if (m_symbol == stdx::big_int_symbol::positive)
	{
		while (this->operator>=(v))
		{
			this->operator-=(v);
		}
	}
	else if (m_symbol == stdx::big_int_symbol::negative)
	{
		while (this->operator<=(v))
		{
			this->operator+=(v);
		}
	}
}

void stdx::big_int::operator%=(uint16_t v)
{
	if (v == 0)
	{
		throw std::domain_error("cann't divided by 0");
	}
	if (v == 1)
	{
		this->operator=(0);
		return;
	}
	if (this->operator==(0))
	{
		return;
	}
	if (m_symbol == stdx::big_int_symbol::positive)
	{
		while (this->operator>=(v))
		{
			this->operator-=(v);
		}
	}
	else if (m_symbol == stdx::big_int_symbol::negative)
	{
		while (this->operator<=(v))
		{
			this->operator+=(v);
		}
	}
}

void stdx::big_int::operator%=(uint32_t v)
{
	if (v == 0)
	{
		throw std::domain_error("cann't divided by 0");
	}
	if (v == 1)
	{
		this->operator=(0);
		return;
	}
	if (this->operator==(0))
	{
		return;
	}
	if (m_symbol == stdx::big_int_symbol::positive)
	{
		while (this->operator>=(v))
		{
			this->operator-=(v);
		}
	}
	else if (m_symbol == stdx::big_int_symbol::negative)
	{
		while (this->operator<=(v))
		{
			this->operator+=(v);
		}
	}
}

void stdx::big_int::operator%=(uint64_t v)
{
	if (v == 0)
	{
		throw std::domain_error("cann't divided by 0");
	}
	if (v == 1)
	{
		this->operator=(0);
		return;
	}
	if (this->operator==(0))
	{
		return;
	}
	if (m_symbol == stdx::big_int_symbol::positive)
	{
		while (this->operator>=(v))
		{
			this->operator-=(v);
		}
	}
	else if (m_symbol == stdx::big_int_symbol::negative)
	{
		while (this->operator<=(v))
		{
			this->operator+=(v);
		}
	}
}

void stdx::big_int::operator%=(const stdx::big_int& other)
{
	if (other == 0)
	{
		throw std::domain_error("cann't divided by 0");
	}
	if (this->operator==(0))
	{
		return;
	}
	if (other == 1 || other == -1)
	{
		this->operator=(0);
		return;
	}
	if (other < 0)
	{
		if (m_symbol == stdx::big_int_symbol::positive)
		{
			while (this->operator>=(other))
			{
				this->operator+=(other);
			}
			m_symbol = stdx::big_int_symbol::negative;
		}
		else if (m_symbol == stdx::big_int_symbol::negative)
		{
			while (this->operator<=(other))
			{
				this->operator-=(other);
			}
			m_symbol = stdx::big_int_symbol::positive;
		}
	}
	else
	{
		if (m_symbol == stdx::big_int_symbol::positive)
		{
			while (this->operator>=(other))
			{
				this->operator-=(other);
			}
		}
		else if (m_symbol == stdx::big_int_symbol::negative)
		{
			while (this->operator<=(other))
			{
				this->operator+=(other);
			}
		}
	}
}

void stdx::big_int::operator<<=(const size_t& n)
{
	for (size_t i = 0; i < n; i++)
	{
		this->operator*=(2);
	}
}

void stdx::big_int::operator>>=(const size_t& n)
{
	for (size_t i = 0; i < n; i++)
	{
		this->operator/=(2);
	}
}

void stdx::big_int::_BitOr(byte_t* buffer, const size_t& buffer_size)
{
	size_t size = m_data.size();
	if (size <= buffer_size)
	{
		for (size_t i = 0; i < size; i++)
		{
			m_data.at(i) |= buffer[i];
		}
	}
	else
	{
		for (size_t i = 0; i < buffer_size; i++)
		{
			m_data.at(i) |= buffer[i];
		}
	}
	uint8_t tmp = 0;
	if (_BitCompareWith((byte_t*)&tmp,sizeof(uint8_t))==0)
	{
		m_symbol = stdx::big_int_symbol::zero;
		m_data.clear();
	}
}

void stdx::big_int::_BitOr(const std::vector<byte_t>& other)
{
	size_t size = m_data.size(),other_size = other.size();
	if (size <= other_size)
	{
		for (size_t i = 0; i < size; i++)
		{
			m_data.at(i) |= other.at(i);
		}
	}
	else
	{
		for (size_t i = 0; i < other_size; i++)
		{
			m_data.at(i) |= other.at(i);
		}
	}
	uint8_t tmp = 0;
	if (_BitCompareWith((byte_t*)&tmp, sizeof(uint8_t)) == 0)
	{
		m_symbol = stdx::big_int_symbol::zero;
		m_data.clear();
	}
}

void stdx::big_int::_BitXor(byte_t* buffer, const size_t& buffer_size)
{
	size_t size = m_data.size();
	if (size == buffer_size)
	{
		for (size_t i = 0; i < size; i++)
		{
			m_data.at(i) ^= buffer[i];
		}
	}
	else if (size > buffer_size)
	{
		for (size_t i = 0; i < buffer_size; i++)
		{
			m_data.at(i) ^= buffer[i];
		}
		for (size_t i = buffer_size; i < size; i++)
		{
			m_data.at(i) ^= 0x00;
		}
	}
	uint8_t tmp = 0;
	if (_BitCompareWith((byte_t*)&tmp, sizeof(uint8_t)) == 0)
	{
		m_symbol = stdx::big_int_symbol::zero;
		m_data.clear();
	}
}

void stdx::big_int::_BitXor(const std::vector<byte_t>& other)
{
	size_t size = m_data.size(),other_size = other.size();
	if (size == other_size)
	{
		for (size_t i = 0; i < size; i++)
		{
			m_data.at(i) ^= other.at(i);
		}
	}
	else if (size > other_size)
	{
		for (size_t i = 0; i < other_size; i++)
		{
			m_data.at(i) ^= m_data.at(i);
		}
		for (size_t i = other_size; i < size; i++)
		{
			m_data.at(i) ^= 0x00;
		}
	}
	uint8_t tmp = 0;
	if (_BitCompareWith((byte_t*)&tmp, sizeof(uint8_t)) == 0)
	{
		m_symbol = stdx::big_int_symbol::zero;
		m_data.clear();
	}
}

void stdx::big_int::_BitAnd(byte_t* buffer, const size_t& buffer_size)
{
	size_t size = m_data.size();
	if (size <= buffer_size)
	{
		for (size_t i = 0; i < size; i++)
		{
			m_data.at(i) &= buffer[i];
		}
	}
	else
	{
		for (size_t i = 0; i < buffer_size; i++)
		{
			m_data.at(i) &= buffer[i];
		}
		auto begin = m_data.begin() + buffer_size, end = m_data.end();
		m_data.erase(begin, end);
	}
	uint8_t tmp = 0;
	if (_BitCompareWith((byte_t*)&tmp, sizeof(uint8_t)) == 0)
	{
		m_symbol = stdx::big_int_symbol::zero;
		m_data.clear();
	}
}

void stdx::big_int::_BitAnd(const std::vector<byte_t>& other)
{
	size_t size = m_data.size(),other_size = other.size();
	if (size <= other_size)
	{
		for (size_t i = 0; i < size; i++)
		{
			m_data.at(i) &= other.at(i);
		}
	}
	else
	{
		for (size_t i = 0; i < other_size; i++)
		{
			m_data.at(i) &= other.at(i);
		}
		auto begin = m_data.begin() + other_size, end = m_data.end();
		m_data.erase(begin, end);
	}
	uint8_t tmp = 0;
	if (_BitCompareWith((byte_t*)&tmp, sizeof(uint8_t)) == 0)
	{
		m_symbol = stdx::big_int_symbol::zero;
		m_data.clear();
	}
}

void stdx::big_int::operator|=(int8_t v)
{
	_BitOr((byte_t*)&v,sizeof(v));
}

void stdx::big_int::operator|=(int16_t v)
{
	_BitOr((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator|=(int32_t v)
{
	_BitOr((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator|=(int64_t v)
{
	_BitOr((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator|=(uint8_t v)
{
	_BitOr((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator|=(uint16_t v)
{
	_BitOr((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator|=(uint32_t v)
{
	_BitOr((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator|=(uint64_t v)
{
	_BitOr((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator|=(const stdx::big_int& other)
{
	_BitOr(other.m_data);
}

void stdx::big_int::operator^=(int8_t v)
{
	_BitXor((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator^=(int16_t v)
{
	_BitXor((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator^=(int32_t v)
{
	_BitXor((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator^=(int64_t v)
{
	_BitXor((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator^=(uint8_t v)
{
	_BitXor((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator^=(uint16_t v)
{
	_BitXor((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator^=(uint32_t v)
{
	_BitXor((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator^=(uint64_t v)
{
	_BitXor((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator^=(const stdx::big_int& other)
{
	_BitXor(other.m_data);
}

void stdx::big_int::operator&=(int8_t v)
{
	if (v==0)
	{
		this->operator=(0);
		return;
	}
	_BitAnd((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator&=(int16_t v)
{
	if (v == 0)
	{
		this->operator=(0);
		return;
	}
	_BitAnd((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator&=(int32_t v)
{
	if (v == 0)
	{
		this->operator=(0);
		return;
	}
	_BitAnd((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator&=(int64_t v)
{
	if (v == 0)
	{
		this->operator=(0);
		return;
	}
	_BitAnd((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator&=(uint8_t v)
{
	if (v == 0)
	{
		this->operator=(0);
		return;
	}
	_BitAnd((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator&=(uint16_t v)
{
	if (v == 0)
	{
		this->operator=(0);
		return;
	}
	_BitAnd((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator&=(uint32_t v)
{
	if (v == 0)
	{
		this->operator=(0);
		return;
	}
	_BitAnd((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator&=(uint64_t v)
{
	if (v == 0)
	{
		this->operator=(0);
		return;
	}
	_BitAnd((byte_t*)&v, sizeof(v));
}

void stdx::big_int::operator&=(const stdx::big_int& other)
{
	if (other == 0)
	{
		this->operator=(0);
		return;
	}
	_BitAnd(other.m_data);
}

typename stdx::string::char_t stdx::big_int::_ByteToUChar(byte_t v)
{
	switch (v)
	{
	case 0x00:
		return U('0');
	case 0x01:
		return U('1');
	case 0x02:
		return U('2');
	case 0x03:
		return U('3');
	case 0x04:
		return U('4');
	case 0x05:
		return U('5');
	case 0x06:
		return U('6');
	case 0x07:
		return U('7');
	case 0x08:
		return U('8');
	case 0x09:
		return U('9');
	case 0x0A:
		return U('A');
	case 0x0B:
		return U('B');
	case 0x0C:
		return U('C');
	case 0x0D:
		return U('D');
	case 0x0E:
		return U('E');
	case 0x0F:
		return U('F');
	default:
		throw std::domain_error("out of domain! should input 0x00 to 0x0F");
	}
}

stdx::string stdx::big_int::to_hex_string() const
{
	stdx::string str = U("0x");
	for (auto begin = m_data.rbegin(),end=m_data.rend();begin!=end;begin++)
	{
		byte_t tmp = *begin & 0xF0;
		tmp >>= 4;
		str.push_back(_ByteToUChar(tmp));
		tmp = *begin & 0x0F;
		str.push_back(_ByteToUChar(tmp));
	}
	return str;
}

stdx::string stdx::big_int::to_hex_string_without_0x() const
{
	stdx::string str;
	for (auto begin = m_data.rbegin(), end = m_data.rend(); begin != end; begin++)
	{
		byte_t tmp = *begin & 0xF0;
		tmp >>= 4;
		str.push_back(_ByteToUChar(tmp));
		tmp = *begin & 0x0F;
		str.push_back(_ByteToUChar(tmp));
	}
	return str;
}

typename stdx::big_int::byte_t stdx::big_int::_UCharToByte(const typename stdx::string::char_t& ch)
{
	switch (ch)
	{
	case U('0'):
		return 0x00;
	case U('1'):
		return 0x01;
	case U('2'):
		return 0x02;
	case U('3'):
		return 0x03;
	case U('4'):
		return 0x04;
	case U('5'):
		return 0x05;
	case U('6'):
		return 0x06;
	case U('7'):
		return 0x07;
	case U('8'):
		return 0x08;
	case U('9'):
		return 0x09;
	case U('A'):
		return 0x0A;
	case U('B'):
		return 0x0B;
	case U('C'):
		return 0x0C;
	case U('D'):
		return 0x0D;
	case U('E'):
		return 0x0E;
	case U('F'):
		return 0x0F;
	case U('a'):
		return 0x0A;
	case U('b'):
		return 0x0B;
	case U('c'):
		return 0x0C;
	case U('d'):
		return 0x0D;
	case U('e'):
		return 0x0E;
	case U('f'):
		return 0x0F;
	default:
		throw std::domain_error("this char cannot change into byte_t");
	}
}

stdx::big_int stdx::big_int::from_hex_string(const stdx::string& hex)
{
	stdx::string tmp(hex);
	return stdx::big_int::from_hex_string(std::move(tmp));
}

stdx::big_int stdx::big_int::from_hex_string(stdx::string &&hex)
{
	hex.replace(U("0x"), U("")).replace(U("0X"),U(""));
	if (hex.empty())
	{
		throw std::invalid_argument("hex string cannot be empty");
	}
	if (hex.front() == U('-'))
	{
		hex.erase(hex.begin());
		std::vector<byte_t> container;
		if (hex.size() % 2)
		{
			for (int64_t i = hex.size() - 1; true; i -= 2)
			{
				if (i <= 0)
				{
					break;
				}
				byte_t t1 = _UCharToByte(hex.at(i));
				byte_t t2 = _UCharToByte(hex.at(i - 1));
				t2 <<= 4;
				t1 |= t2;
				container.push_back(t1);
			}
			byte_t tmp = _UCharToByte(hex.at(hex.size() - 1));
			container.push_back(tmp);
		}
		else
		{
			for (int64_t i = hex.size() - 1; true; i -= 2)
			{
				if (i <= 0)
				{
					break;
				}
				byte_t t1 = _UCharToByte(hex.at(i));
				byte_t t2 = _UCharToByte(hex.at(i - 1));
				t2 <<= 4;
				t1 |= t2;
				container.push_back(t1);
			}
		}
		stdx::big_int tmp(container);
		if (tmp != 0)
		{
			tmp.m_symbol = stdx::big_int_symbol::negative;
		}
		return tmp;
	}
	std::vector<byte_t> container;
	if (hex.size() % 2)
	{
		for (int64_t i = hex.size()-1;true; i-=2)
		{
			if (i <= 0)
			{
				break;
			}
			byte_t t1 = _UCharToByte(hex.at(i));
			byte_t t2 = _UCharToByte(hex.at(i - 1));
			t2 <<= 4;
			t1 |= t2;
			container.push_back(t1);
		}
		byte_t tmp = _UCharToByte(hex.at(hex.size() - 1));
		container.push_back(tmp);
	}
	else
	{
		for (int64_t i = hex.size() - 1; true;i-=2)
		{
			if (i <= 0)
			{
				break;
			}
			byte_t t1 = _UCharToByte(hex.at(i));
			byte_t t2 = _UCharToByte(hex.at(i-1));
			t2 <<= 4;
			t1 |= t2;
			container.push_back(t1);
		}
	}
	return stdx::big_int(container);
}