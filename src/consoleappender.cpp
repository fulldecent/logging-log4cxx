/*
 * Copyright 2003,2005 The Apache Software Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <log4cxx/consoleappender.h>
#include <log4cxx/helpers/loglog.h>
#include <log4cxx/helpers/systemoutwriter.h>
#include <log4cxx/helpers/systemerrwriter.h>
#include <log4cxx/helpers/stringhelper.h>
#include <log4cxx/layout.h>

using namespace log4cxx;
using namespace log4cxx::helpers;

IMPLEMENT_LOG4CXX_OBJECT(ConsoleAppender)

ConsoleAppender::ConsoleAppender()
 : target(getSystemOut())
{
}

ConsoleAppender::ConsoleAppender(const LayoutPtr& layout)
 :target(getSystemOut())
{
    setLayout(layout);
    WriterPtr wr(createWriter(getSystemOut()));
    setWriter(wr);
    Pool p;
    WriterAppender::activateOptions(p);
}

ConsoleAppender::ConsoleAppender(const LayoutPtr& layout, const LogString& target)
 : target(target)
{
      setLayout(layout);
      WriterPtr wr(createWriter(target));
      setWriter(wr);
      Pool p;
      WriterAppender::activateOptions(p);
}

ConsoleAppender::~ConsoleAppender()
{
        finalize();
}

const LogString& ConsoleAppender::getSystemOut() {
  static const LogString name(LOG4CXX_STR("System.out"));
  return name;
}

const LogString& ConsoleAppender::getSystemErr() {
  static const LogString name(LOG4CXX_STR("System.err"));
  return name;
}

WriterPtr ConsoleAppender::createWriter(const LogString& value) {
  LogString v = StringHelper::trim(value);

  if (StringHelper::equalsIgnoreCase(v,
         LOG4CXX_STR("SYSTEM.ERR"), LOG4CXX_STR("system.err"))) {
          return new SystemErrWriter();
  }
  return new SystemOutWriter();
}

void ConsoleAppender::setTarget(const LogString& value)
{
        LogString v = StringHelper::trim(value);

        if (StringHelper::equalsIgnoreCase(v,
              LOG4CXX_STR("SYSTEM.OUT"), LOG4CXX_STR("system.out")))
        {
                target = getSystemOut();
        }
        else if (StringHelper::equalsIgnoreCase(v,
               LOG4CXX_STR("SYSTEM.ERR"), LOG4CXX_STR("system.err")))
        {
                target = getSystemErr();
        }
        else
        {
                targetWarn(value);
        }
}

LogString ConsoleAppender::getTarget() const
{
        return target;
}

void ConsoleAppender::targetWarn(const LogString& val)
{
        LogLog::warn(((LogString) LOG4CXX_STR("["))
           + val +  LOG4CXX_STR("] should be system.out or system.err."));
        LogLog::warn(LOG4CXX_STR("Using previously set target, System.out by default."));
}

void ConsoleAppender::activateOptions(Pool& p)
{
        if(StringHelper::equalsIgnoreCase(target,
              LOG4CXX_STR("SYSTEM.OUT"), LOG4CXX_STR("system.out")))
        {
                WriterPtr writer(new SystemOutWriter());
                setWriter(writer);
        }
        else if (StringHelper::equalsIgnoreCase(target,
              LOG4CXX_STR("SYSTEM.ERR"), LOG4CXX_STR("system.err")))
        {
              WriterPtr writer(new SystemErrWriter());
              setWriter(writer);
        }
        WriterAppender::activateOptions(p);
}

void ConsoleAppender::setOption(const LogString& option, const LogString& value)
{
        if (StringHelper::equalsIgnoreCase(option,
              LOG4CXX_STR("TARGET"), LOG4CXX_STR("target")))
        {
                setTarget(value);
        }
        else
        {
                WriterAppender::setOption(option, value);
        }
}






