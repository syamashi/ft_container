
namespace ft
{
	// デストラクタで呼ぶだけ
	template < typename Func >
	class scope_exit {
		private:
			Func func ;
		public:
			scope_exit( Func func ) : func(func) { }
			~scope_exit() { func() ; }
	} ;

	template < typename Func >
	static scope_exit< Func > make_scope_exit( Func func ) { return scope_exit<Func>(func) ; }
}