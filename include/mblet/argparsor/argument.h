/**
 * argparsor/argument.h
 *
 * Licensed under the MIT License <http://opensource.org/licenses/MIT>.
 * Copyright (c) 2022-2023 BLET Mickaël.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef _MBLET_ARGPARSOR_ARGUMENT_H_
#define _MBLET_ARGPARSOR_ARGUMENT_H_

#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "mblet/argparsor/action.h"
#include "mblet/argparsor/exception.h"
#include "mblet/argparsor/valid.h"
#include "mblet/argparsor/vector.h"

namespace mblet {

class Argparsor;

namespace argparsor {

template<typename T>
inline void boolTo(const bool&, T&) {
    throw ParseArgumentException("destination method not found for this type");
}

inline void boolTo(const bool& b, bool& ret) {
    ret = b;
}

inline void boolTo(const bool& b, char& ret) {
    ret = b;
}

inline void boolTo(const bool& b, unsigned char& ret) {
    ret = b;
}

inline void boolTo(const bool& b, short& ret) {
    ret = b;
}

inline void boolTo(const bool& b, unsigned short& ret) {
    ret = b;
}

inline void boolTo(const bool& b, int& ret) {
    ret = b;
}

inline void boolTo(const bool& b, unsigned int& ret) {
    ret = b;
}

inline void boolTo(const bool& b, long& ret) {
    ret = b;
}

inline void boolTo(const bool& b, unsigned long& ret) {
    ret = b;
}

#if __cplusplus >= 201103L
#ifdef _GLIBCXX_USE_LONG_LONG

inline void boolTo(const bool& b, long long& ret) {
    ret = b;
}

inline void boolTo(const bool& b, unsigned long long& ret) {
    ret = b;
}

#endif
#endif

inline void boolTo(const bool& b, float& ret) {
    ret = b;
}

inline void boolTo(const bool& b, double& ret) {
    ret = b;
}

inline void boolTo(const bool& b, long double& ret) {
    ret = b;
}

inline void boolTo(const bool& b, std::string& ret) {
    if (b) {
        ret = "true";
    }
    else {
        ret = "false";
    }
}

inline void boolTo(const bool& b, const char*& ret) {
    if (b) {
        ret = "true";
    }
    else {
        ret = "false";
    }
}

template<std::size_t Size>
inline void boolTo(const bool& b, char (&ret)[Size]) {
    if (b) {
        if (Size >= sizeof("true")) {
            ::memcpy(ret, "true", sizeof("true"));
        }
        else {
            ::memcpy(ret, "true", Size - 1);
            ret[Size - 1] = '\0';
        }
    }
    else {
        if (Size >= sizeof("false")) {
            ::memcpy(ret, "false", sizeof("false"));
        }
        else {
            ::memcpy(ret, "false", Size - 1);
            ret[Size - 1] = '\0';
        }
    }
}

template<typename T>
inline void strTo(const std::string&, T&) {
    throw ParseArgumentException("destination method not found for this type");
}

inline void strTo(const std::string& str, bool& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

inline void strTo(const std::string& str, char& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

inline void strTo(const std::string& str, unsigned char& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

inline void strTo(const std::string& str, short& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

inline void strTo(const std::string& str, unsigned short& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

inline void strTo(const std::string& str, int& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

inline void strTo(const std::string& str, unsigned int& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

inline void strTo(const std::string& str, long& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

inline void strTo(const std::string& str, unsigned long& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

#if __cplusplus >= 201103L
#ifdef _GLIBCXX_USE_LONG_LONG

inline void strTo(const std::string& str, long long& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

inline void strTo(const std::string& str, unsigned long long& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

#endif
#endif

inline void strTo(const std::string& str, float& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

inline void strTo(const std::string& str, double& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

inline void strTo(const std::string& str, long double& ret) {
    ret = ::strtod(str.c_str(), NULL);
}

inline void strTo(const std::string& str, std::string& ret) {
    ret = str;
}

inline void strTo(const std::string& str, const char*& ret) {
    ret = str.c_str();
}

template<std::size_t Size>
inline void strTo(const std::string& str, char (&ret)[Size]) {
    if (Size > str.size()) {
        ::memcpy(ret, str.c_str(), str.size());
        ret[str.size()] = '\0';
    }
    else {
        ::memcpy(ret, str.c_str(), Size - 1);
        ret[Size - 1] = '\0';
    }
}

class Argparsor;

class ArgumentElement : public std::vector<ArgumentElement> {
    friend class ::mblet::Argparsor;
    friend class Argparsor;
    friend class Argument;

  public:
    ArgumentElement();
    ArgumentElement(const ArgumentElement& rhs);
    ArgumentElement(const char* arg_, const char* default_);
    ArgumentElement(const char* arg);
    ~ArgumentElement();

    const std::string& getString() const {
        return _argument;
    }

    const std::string& getDefault() const {
        return _default;
    }

    bool isNumber() const {
        return _isNumber;
    }

    double getNumber() const {
        if (_isNumber) {
            return _number;
        }
        throw Exception("is not a number");
    }

    /**
     * @brief tranform to vector of string
     *
     * @return std::vector<std::string>
     */
    operator std::vector<std::string>() const;

    /**
     * @brief Friend function for convert Argument object to ostream
     *
     * @param os
     * @param argument
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, const ArgumentElement& argument) {
        os << argument.getString();
        return os;
    }

  protected:
    std::string _argument;
    std::string _default;
    bool _isNumber;
    double _number;
};

template<typename T>
class ArgumentType;

template<typename T>
class ArgumentVectorType;

template<typename T>
class ArgumentVectorVectorType;

/**
 * @brief Argument object
 */
class Argument : public ArgumentElement {
    friend class ::mblet::Argparsor;
    friend class Argparsor;

  public:
    /**
     * @brief Construct a new Argument object
     */
    Argument(Argparsor& argparsor);

    /**
     * @brief Copy a Argument object
     *
     * @param rhs
     */
    Argument(const Argument& rhs);

    /**
     * @brief Destroy the Argument object
     */
    virtual ~Argument();

    bool isExist() const {
        return _isExist;
    }

    bool isRequired() const {
        return _isRequired;
    }

    std::size_t count() const {
        return _count;
    }

    std::size_t getNargs() const {
        return _nargs;
    }

    const std::string& getHelp() const {
        return _help;
    }

    const std::string& getMetavar() const {
        return _metavar;
    }

    const std::vector<std::string>& getNameOrFlags() const {
        return _nameOrFlags;
    }

    const std::vector<std::string>& getDefaults() const {
        return _defaults;
    }

    Action::eAction getAction() const {
        return _action;
    }

    std::string getString() const;

    /**
     * @brief Override bool operator
     *
     * @return true if exist or false if not exist
     */
    operator bool() const {
        if (_type == REVERSE_BOOLEAN_OPTION) {
            return !_isExist;
        }
        else {
            return _isExist;
        }
    }

    /**
     * @brief tranform to string
     *
     * @return std::string
     */
    operator std::string() const {
        return getString();
    }

    /**
     * @brief tranform to vector of string
     *
     * @return std::vector<std::string>
     */
    operator std::vector<std::string>() const;

    /**
     * @brief tranform to vector of vector of string
     *
     * @return std::vector<std::vector<std::string> >
     */
    operator std::vector<std::vector<std::string> >() const;

    template<typename T>
    operator T() const {
        return getNumber();
    }

    /**
     * @brief overide brakcet operator
     *
     * @param index
     * @return const Argument&
     */
    const ArgumentElement& operator[](unsigned long index) const {
        return at(index);
    }

    /**
     * @brief Option strings, e.g. -f, --foo
     * @param flag_
     * @return this reference
     */
    Argument& flag(const char* flag_);

    /**
     * @brief The basic type of action to be taken when this argument is encountered at the command line
     * @param action_
     * @return this reference
     */
    Argument& action(enum Action::eAction action_) {
        _action = action_;
        _typeConstructor();
        _defaultsConstructor();
        return *this;
    }

    /**
     * @brief A brief description of what the argument does
     * @param help_
     * @return this reference
     */
    Argument& help(const char* help_) {
        _help = help_;
        return *this;
    }

    /**
     * @brief Whether or not the command-line option may be omitted (optionals only)
     * @param required_
     * @return this reference
     */
    Argument& required(bool required_);

    /**
     * @brief A name for the argument in usage messages
     * @param metavar_
     * @return this reference
     */
    Argument& metavar(const char* metavar_) {
        _metavar = metavar_;
        return *this;
    }

    /**
     * @brief The number of command-line arguments that should be consumed
     * @param nargs_
     * @return this reference
     */
    Argument& nargs(std::size_t nargs_) {
        _nargs = nargs_;
        _typeConstructor();
        _defaultsConstructor();
        return *this;
    }

    /**
     * @brief The value produced if the argument is absent from the command line
     * @param defaults_
     * @return this reference
     */
    Argument& defaults(const Vector& defaults_) {
        _defaults = defaults_;
        _defaultsConstructor();
        return *this;
    }

    /**
     * @brief New object from IValid interface
     * @param pValid
     * @return this reference
     */
    Argument& valid(IValid* pValid, bool isDeletable = true) {
        if (_valid != NULL && _validDeletable) {
            delete _valid;
        }
        _valid = pValid;
        _validDeletable = isDeletable;
        return *this;
    }

    /**
     * @brief define a reference of object for insert the value after parseArguments method
     *
     * @tparam T
     * @param dest
     * @return reference of new argument
     */
    template<typename T>
    Argument& dest(std::vector<std::vector<T> >& dest,
                   void (*toDest)(std::vector<std::vector<T> >& dest, bool isExist,
                                  const std::vector<std::vector<std::string> >& arguments) = NULL) {
        bool validDeletable = _validDeletable;
        _validDeletable = false;
        Argument* argumentType = new ArgumentVectorVectorType<T>(this, dest, toDest);
        argumentType->_validDeletable = validDeletable;
        return *argumentType;
    }

    /**
     * @brief define a reference of object for insert the value after parseArguments method
     *
     * @tparam T
     * @param dest
     * @return reference of new argument
     */
    template<typename T>
    Argument& dest(std::vector<T>& dest, void (*toDest)(std::vector<T>& dest, bool isExist,
                                                        const std::vector<std::string>& arguments) = NULL) {
        bool validDeletable = _validDeletable;
        _validDeletable = false;
        Argument* argumentType = new ArgumentVectorType<T>(this, dest, toDest);
        argumentType->_validDeletable = validDeletable;
        return *argumentType;
    }

    /**
     * @brief define a reference of object for insert the value after parseArguments method
     *
     * @tparam T
     * @param dest
     * @return reference of new argument
     */
    template<typename T>
    Argument& dest(T& dest, void (*toDest)(T& dest, bool isExist, const std::string& argument) = NULL) {
        bool validDeletable = _validDeletable;
        _validDeletable = false;
        Argument* argumentType = new ArgumentType<T>(this, dest, toDest);
        argumentType->_validDeletable = validDeletable;
        return *argumentType;
    }

    /**
     * @brief Friend function for convert Argument object to ostream
     *
     * @param os
     * @param argument
     * @return std::ostream&
     */
    friend std::ostream& operator<<(std::ostream& os, const Argument& argument) {
        os << argument.getString();
        return os;
    }

  protected:
    enum Type {
        NONE = 0,
        HELP_OPTION,
        VERSION_OPTION,
        BOOLEAN_OPTION,
        REVERSE_BOOLEAN_OPTION,
        SIMPLE_OPTION,
        NUMBER_OPTION,
        INFINITE_OPTION,
        MULTI_OPTION,
        MULTI_INFINITE_OPTION,
        MULTI_NUMBER_OPTION,
        MULTI_NUMBER_INFINITE_OPTION,
        POSITIONAL_ARGUMENT,
        NUMBER_POSITIONAL_ARGUMENT,
        INFINITE_POSITIONAL_ARGUMENT,
        INFINITE_NUMBER_POSITIONAL_ARGUMENT
    };

    bool _isPositionnalArgument() const {
        switch (_type) {
            case POSITIONAL_ARGUMENT:
            case NUMBER_POSITIONAL_ARGUMENT:
            case INFINITE_POSITIONAL_ARGUMENT:
            case INFINITE_NUMBER_POSITIONAL_ARGUMENT:
                return true;
            default:
                return false;
        }
    }

    virtual void _toDest() {
        /* do nothing */
    }

    void _toNumber();

    std::string _metavarDefault();

    void _typeConstructor();

    void _defaultsConstructor();

    void _sortNameOrFlags();

    static void validFormatFlag(const char* flag);

    static bool compareOption(const Argument* first, const Argument* second);

    Argparsor& _argparsor;

    std::vector<std::string> _nameOrFlags;
    enum Type _type;
    bool _isExist;
    bool _isRequired;
    std::size_t _count;
    std::size_t _nargs;
    std::string _help;
    std::string _metavar;

    IValid* _valid;
    bool _validDeletable;

    Argument** _this;
    enum Action::eAction _action;
    std::vector<std::string> _defaults;
};

template<typename T>
class ArgumentType : public Argument {
  public:
    ArgumentType(Argument* argument, T& dest, void (*toDest)(T&, bool, const std::string&)) :
        Argument(*argument),
        _dest(dest),
        _toDestCustom(toDest) {
        delete argument;
        *_this = this;
    }
    virtual ~ArgumentType() {}

  private:
    void _toDest() {
        if (_toDestCustom != NULL) {
            _toDestCustom(_dest, _isExist, _argument);
        }
        else {
            if (_type == BOOLEAN_OPTION) {
                boolTo(_isExist, _dest);
            }
            else if (_type == REVERSE_BOOLEAN_OPTION) {
                boolTo(!_isExist, _dest);
            }
            else {
                strTo(_argument, _dest);
            }
        }
    }

    T& _dest;
    void (*_toDestCustom)(T&, bool, const std::string&);
};

template<typename T>
class ArgumentVectorType : public Argument {
  public:
    ArgumentVectorType(Argument* argument, std::vector<T>& dest,
                       void (*toDest)(std::vector<T>&, bool, const std::vector<std::string>&)) :
        Argument(*argument),
        _dest(dest),
        _toDestCustom(toDest) {
        delete argument;
        *_this = this;
    }
    virtual ~ArgumentVectorType() {}

  private:
    void _toDest() {
        if (_toDestCustom != NULL) {
            std::vector<std::string> arguments;
            if (!empty()) {
                for (std::size_t i = 0; i < size(); ++i) {
                    if (!at(i).empty()) {
                        for (std::size_t j = 0; j < at(i).size(); ++j) {
                            arguments.push_back(at(i).at(j).getString());
                        }
                    }
                    else {
                        arguments.push_back(at(i).getString());
                    }
                }
            }
            else {
                arguments.push_back(_argument);
            }
            _toDestCustom(_dest, _isExist, arguments);
        }
        else {
            if (!empty()) {
                for (std::size_t i = 0; i < size(); ++i) {
                    if (!at(i).empty()) {
                        for (std::size_t j = 0; j < at(i).size(); ++j) {
                            T dest;
                            strTo(at(i).at(j).getString(), dest);
                            _dest.push_back(dest);
                        }
                    }
                    else {
                        T dest;
                        strTo(at(i).getString(), dest);
                        _dest.push_back(dest);
                    }
                }
            }
            else {
                T dest;
                if (_type == BOOLEAN_OPTION) {
                    boolTo(_isExist, dest);
                }
                else if (_type == REVERSE_BOOLEAN_OPTION) {
                    boolTo(!_isExist, dest);
                }
                else {
                    strTo(_argument, dest);
                }
                _dest.push_back(dest);
            }
        }
    }

    std::vector<T>& _dest;
    void (*_toDestCustom)(std::vector<T>&, bool, const std::vector<std::string>&);
};

template<typename T>
class ArgumentVectorVectorType : public Argument {
  public:
    ArgumentVectorVectorType(Argument* argument, std::vector<std::vector<T> >& dest,
                             void (*toDest)(std::vector<std::vector<T> >&, bool,
                                            const std::vector<std::vector<std::string> >&)) :
        Argument(*argument),
        _dest(dest),
        _toDestCustom(toDest) {
        delete argument;
        *_this = this;
    }
    virtual ~ArgumentVectorVectorType() {}

  private:
    void _toDest() {
        if (_toDestCustom != NULL) {
            std::vector<std::vector<std::string> > arguments;
            if (!empty()) {
                for (std::size_t i = 0; i < size(); ++i) {
                    std::vector<std::string> tmpVector;
                    if (!at(i).empty()) {
                        for (std::size_t j = 0; j < at(i).size(); ++j) {
                            tmpVector.push_back(at(i).at(j).getString());
                        }
                    }
                    else {
                        tmpVector.push_back(at(i).getString());
                    }
                    arguments.push_back(tmpVector);
                }
            }
            else {
                std::vector<std::string> tmpVector;
                tmpVector.push_back(_argument);
                arguments.push_back(tmpVector);
            }
            _toDestCustom(_dest, _isExist, arguments);
        }
        else {
            if (!empty()) {
                for (std::size_t i = 0; i < size(); ++i) {
                    std::vector<T> vectorDest;
                    if (!at(i).empty()) {
                        for (std::size_t j = 0; j < at(i).size(); ++j) {
                            T dest;
                            strTo(at(i).at(j).getString(), dest);
                            vectorDest.push_back(dest);
                        }
                    }
                    else {
                        T dest;
                        strTo(at(i).getString(), dest);
                        vectorDest.push_back(dest);
                    }
                    _dest.push_back(vectorDest);
                }
            }
            else {
                T dest;
                if (_type == BOOLEAN_OPTION) {
                    boolTo(_isExist, dest);
                }
                else if (_type == REVERSE_BOOLEAN_OPTION) {
                    boolTo(!_isExist, dest);
                }
                else {
                    strTo(_argument, dest);
                }
                std::vector<T> vectorDest;
                vectorDest.push_back(dest);
                _dest.push_back(vectorDest);
            }
        }
    }

    std::vector<std::vector<T> >& _dest;
    void (*_toDestCustom)(std::vector<std::vector<T> >&, bool, const std::vector<std::vector<std::string> >&);
};

} // namespace argparsor

} // namespace mblet

#endif // #ifndef _MBLET_ARGPARSOR_ARGUMENT_H_