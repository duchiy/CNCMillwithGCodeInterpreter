#include "stdafx.h"
#include <assert.h> 
#ifndef __SINGLETON_H__
#define __SINGLETON_H__

template <typename T> 
class RSingleton
{
	public:
       
		//! Gets a reference to the instance of the singleton class.
		/*!
			\return A reference to the instance of the singleton class.
			If there is no instance of the class yet, one will be created.
		*/
		static T & Instance()
		{
			static T m_instance; //!< singleton class instance
			return m_instance;
		};
   
		//! Destroys the singleton class instance.
		/*!
			Be aware that all references to the single class instance will be
			invalid after this method has been executed!
		*/
		static void DestroyInstance(void )
		{
	};
  
	protected:
   
		// shield the constructor and destructor to prevent outside sources
		// from creating or destroying a RSingleton instance.
   
		//! Default constructor.
		RSingleton()
		{
		};
   
		//! Copy constructor.
		RSingleton(const RSingleton& source)
		{
		};
 
		RSingleton & operator=(const RSingleton& source)
		{
			
			return *this;
		};

		//! Destructor.
		virtual ~RSingleton()
		{
		};
   
	private:
   
};

#endif // ! defined __SINGLETON_H__